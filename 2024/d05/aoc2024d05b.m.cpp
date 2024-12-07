// https://adventofcode.com/2024/day/5#part2
// C++23
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <new>
#include <print>

#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace {

namespace r4s = std::ranges;

using Rules = std::unordered_multimap<int, int>;
using Update = std::vector<int>;

bool updateLess(Rules const &rules, int a, int b) noexcept {
  auto [f, l] = rules.equal_range(a);
  return std::any_of(f, l, [b](auto &x) { return x.second == b; });
}

bool isInRightOrder(Rules const &rules, Update const &update) noexcept {
  return r4s::is_sorted(
      update, [&rules](int a, int b) { return updateLess(rules, a, b); });
}

void sortInRightOrder(Rules const &rules, Update &update) noexcept {
  r4s::sort(update, [&rules](int a, int b) { return updateLess(rules, a, b); });
}

void solve2024day5b(std::istream &input) {
  Rules pageOrderRules;
  std::string line;
  while (std::getline(input, line), line.size() == 5)
    pageOrderRules.emplace(std::stoi(line.substr(0, 2)),
                           std::stoi(line.substr(3, 2)));
  assert(input);
  assert(line.empty());
  assert(not pageOrderRules.empty());

  int sumOfMid{};

  Update update;
  while (input >> line) {
    update.clear();
    std::istringstream iss{line};
    for (int x; iss >> x;) {
      update.push_back(x);
      char ch{};
      iss >> ch;
      assert(ch == ',' || iss.eof());
    }
    assert(update.size() % 2 == 1);

    if (!isInRightOrder(pageOrderRules, update)) {
      sortInRightOrder(pageOrderRules, update);
      sumOfMid += *(update.begin() + update.size() / 2);
    }
  }

  std::println("Puzzle answer is {}.", sumOfMid);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day5b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
