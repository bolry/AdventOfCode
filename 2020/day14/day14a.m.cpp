#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string_view>
#include <unordered_map>

using namespace std::literals;
using namespace std::ranges;

namespace
{
using Uint36 = std::bitset<36>;
using Mem    = std::unordered_map<int, Uint36>;

struct Mask
{
   Uint36 zeros;  // set bit represent 0's
   Uint36 ones;   // set bits represent 1's
};

}  // namespace

int main()
{
#if 0
   std::istringstream in(
      "mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X\n"
      "mem[8] = 11\n"
      "mem[7] = 101\n"
      "mem[8] = 0\n");
#else
   std::ifstream in("../input.txt");
#endif
   std::string line;
   Mask curMask{};
   Mem mem;
   std::string strMask;
   while(std::getline(in, line))
   {
      constexpr auto kMask = "mask = "sv;
      if(line.starts_with(kMask))
      {
         std::string_view rawMask(line.data() + kMask.size(), Uint36().size());
         strMask = rawMask;
         replace(strMask, 'X', '1');
         curMask.zeros = Uint36(strMask, 0, std::string::npos, '1', '0');
         strMask       = rawMask;
         replace(strMask, 'X', '0');
         curMask.ones = Uint36(strMask);
      }
      else  // mem[n] = ...
      {
         std::istringstream iss(line);
         iss.ignore("mem["sv.size());
         Mem::key_type addr;
         if(iss >> addr)
         {
            iss.ignore(" = "sv.size());
            std::uint_least64_t v;
            iss >> v;
            Uint36 value{v};
            value &= ~curMask.zeros;
            value |= curMask.ones;
            mem[addr] = value;
         }
         else
         {
            assert(false);
         }
      }
   }

   auto answer = std::accumulate(
      begin(mem), end(mem), std::uint_least64_t{}, [](auto a, auto& b) {
         return a + b.second.to_ullong();
      });
   std::cout << answer << std::endl;
}
