#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>

namespace
{
struct Line
{
   int lower{};
   int upper{};
   char ch{};
   std::string passwd;
   friend std::istream& operator>>(std::istream& in, Line& line)
   {
      char dummyColon;
      in >> line.lower >> line.upper >> line.ch >> dummyColon >> line.passwd;
      line.upper = -line.upper;
      return in;
   }
};
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   auto validPasswd = std::count_if(
      std::istream_iterator<Line>(in),
      std::istream_iterator<Line>(),
      [](Line const& line) {
         return (line.passwd[static_cast<std::size_t>(line.lower - 1)] ==
                 line.ch) +
                   (line.passwd[static_cast<std::size_t>(line.upper - 1)] ==
                    line.ch) ==
                1;
      });
   std::cout << "Number of valid passwords " << validPasswd << std::endl;
   return EXIT_SUCCESS;
}
