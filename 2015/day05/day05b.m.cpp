#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

namespace
{
bool hasTwoDoubleSequences(std::string const& str)
{
   static std::regex const re(R"aoc((..).*\1)aoc");
   return std::regex_search(str, re);
}
bool hasLetterOneApart(std::string const& str)
{
   static std::regex const re(R"aoc((.).\1)aoc");
   return std::regex_search(str, re);
}
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   auto const niceStrings = count_if(
      std::istream_iterator<std::string>(in),
      std::istream_iterator<std::string>(),
      [](auto const& str) {
         return hasTwoDoubleSequences(str) && hasLetterOneApart(str);
      });
   std::cout << "There are " << niceStrings << " nice strings.\n" << std::flush;
}
