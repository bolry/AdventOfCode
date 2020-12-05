#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std::ranges;

namespace
{
struct SeatId
{
   int id;
   friend std::istream& operator>>(std::istream& in, SeatId& seat)
   {
      std::string line;
      if(in >> line)
      {
         int row{};
         auto [colStartIter, ignore] = for_each_n(
            cbegin(line), 7, [&row](char const ch) {
               row <<= 1;
               if(ch == 'B')
               {
                  row |= 1;
               }
            });
         int col{};
         for_each_n(colStartIter, 3, [&col](char const ch) {
            col <<= 1;
            if(ch == 'R')
            {
               col |= 1;
            }
         });
         seat.id = row * 8 + col;
      }
      return in;
   }
};
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   std::vector<SeatId> seatIds;
   seatIds.reserve(771);
   copy(
      std::istream_iterator<SeatId>(in),
      std::istream_iterator<SeatId>(),
      back_inserter(seatIds));

   std::cout
      << "Highest seat ID is "
      << max_element(seatIds, [](auto& a, auto& b) { return a.id < b.id; })->id
      << std::endl;
   return EXIT_SUCCESS;
}
