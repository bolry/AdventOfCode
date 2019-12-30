#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

namespace {
bool meetsCriteria(int const numToCheck) {
  auto const str = std::to_string(numToCheck);
  auto const first = cbegin(str);
  auto const last = cend(str);
  return is_sorted(first, last) &&
         (adjacent_find(first, last) != last) &&
         (size(str) == 6U);
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
