#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>

using namespace std::ranges;

namespace
{
using namespace std::string_view_literals;

constexpr auto npos = std::string_view::npos;

bool containsLeastThreeVowels(std::string_view const& str)
{
   return 3 <=
          count_if(str, [](char ch) { return "aeiou"sv.find(ch) != npos; });
}
bool leastOneLetterTwiceInRow(std::string_view const& str)
{
   return adjacent_find(str) != cend(str);
}
bool hasLetterCombo(std::string_view const& str)
{
   return str.find("ab"sv) != npos || str.find("cd"sv) != npos ||
          str.find("pq"sv) != npos || str.find("xy"sv) != npos;
}
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   auto const niceStrings = count_if(
      std::istream_iterator<std::string>(in),
      std::istream_iterator<std::string>(),
      [](auto const& str) {
         return containsLeastThreeVowels(str) &&
                leastOneLetterTwiceInRow(str) && !hasLetterCombo(str);
      });
   std::cout << "There are " << niceStrings << " nice strings.\n" << std::flush;
}
