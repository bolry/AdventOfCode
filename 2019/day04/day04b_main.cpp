#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>

namespace {
bool hasLeastDouble(std::string_view const str) {
  auto const last = cend(str);
  for (auto first = cbegin(str);;) {
    auto match = std::adjacent_find(first, last);
    if (match == last) {
      return false;
    }
    ++match;
    auto third = std::next(match);
    if (third == last || *match != *third) {
      return true;
    }
    first = std::find_if_not(++third, last,
                             [match](auto item) { return item == *match; });
  }
}
bool meetsCriteria(int const numToCheck) {
  auto const str = std::to_string(numToCheck);
  auto const first = cbegin(str);
  auto const last = cend(str);
  return is_sorted(first, last) && hasLeastDouble(str) && (size(str) == 6U);
}
} // namespace

int main() {
  std::cout.exceptions(std::ios_base::badbit | std::ios_base::eofbit |
                       std::ios_base::failbit);

  int passed{};
  for (int numToCheck{128392}; numToCheck <= 643281; ++numToCheck) {
    passed += meetsCriteria(numToCheck);
  }

  std::cout << "Count meeting criteria are " << passed << '\n' << std::flush;

  return EXIT_SUCCESS;
}
