#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std::ranges;

namespace
{
struct BoardingPass
{
   std::uint_least8_t row{};
   std::uint_least8_t column{};
   friend std::istream& operator>>(std::istream& in, BoardingPass& pass)
   {
      std::string line;
      if(in >> line)
      {
         pass = BoardingPass{};

         auto [colStartIter, ignore] = for_each_n(
            cbegin(line), 7, [&pass](char const ch) {
               pass.row <<= 1u;
               if(ch == 'B')
               {
                  pass.row |= 1u;
               }
            });
         for_each_n(colStartIter, 3, [&pass](char const ch) {
            pass.column <<= 1u;
            if(ch == 'R')
            {
               pass.column |= 1u;
            }
         });
      }
      return in;
   }
};
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   std::vector<BoardingPass> passes;
   copy(
      std::istream_iterator<BoardingPass>(in),
      std::istream_iterator<BoardingPass>(),
      back_inserter(passes));
   erase_if(passes, [](BoardingPass const& pass) {
      return pass.row == 0u || pass.row == 127u;
   });
   std::vector<int> seatIds;
   seatIds.reserve(size(passes));
   transform(passes, back_inserter(seatIds), [](auto const& pass) {
      return pass.row * 8u + pass.column;
   });
   sort(seatIds);
   auto seatIdIter = adjacent_find(
      seatIds, [](int a, int b) { return b - a == 2; });
   std::cout << "Your seat ID is " << *seatIdIter + 1 << std::endl;
   return EXIT_SUCCESS;
}
