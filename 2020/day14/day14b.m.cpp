//#define _GLIBCXX_DEBUG
//#define _GLIBCXX_DEBUG_PEDANTIC

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
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
using Mem    = std::unordered_map<std::uint_least64_t, Uint36>;

struct Mask
{
   Uint36 floating;  // set bits represent 0 and 1
   Uint36 ones;      // set bits represent 1's
};

void applyMemAddrDecoder(
   Uint36 const value,
   Mem::key_type addr,
   Mask const& curMask,
   Mem& mem)
{
   Uint36 addrMask{addr};
   addrMask |= curMask.ones;
   addrMask &= ~curMask.floating;
   // address all permutations of floating
   auto nrOfFloats       = curMask.floating.count();
   auto nrOfPermutations = static_cast<unsigned>(std::pow(2, nrOfFloats));
   std::vector<std::size_t> floatOffsets;
   floatOffsets.reserve(nrOfFloats);
   for(std::size_t idx{}, sz = Uint36().size(); nrOfFloats && idx < sz; ++idx)
      if(curMask.floating.test(idx))
         floatOffsets.push_back(idx), --nrOfFloats;
   for(unsigned p{0}; p < nrOfPermutations; ++p)
   {
      auto mask = addrMask;
      std::size_t pos{};
      for(unsigned b{p}; b; b >>= 1)
      {
         if(b & 1U)
            mask.set(floatOffsets[pos]);
         ++pos;
      }
      mem[mask.to_ullong()] = value;
   }
}

}  // namespace

int main()
{
#if 0
   std::istringstream in(
      "mask = 000000000000000000000000000000X1001X\n"
      "mem[42] = 100\n"
      "mask = 00000000000000000000000000000000X0XX\n"
      "mem[26] = 1\n");
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
         replace(strMask, '1', '0');
         curMask.floating = Uint36(strMask, 0, std::string::npos, '0', 'X');
         strMask          = rawMask;
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
            Mem::key_type const value = std::invoke([&iss]() {
               std::uint_least64_t v;
               iss >> v;
               assert(iss);
               return v;
            });
            applyMemAddrDecoder(Uint36(value), addr, curMask, mem);
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
