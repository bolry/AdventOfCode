// https://adventofcode.com/2024/day/7
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

#include <cstdint>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace {

using I = std::intmax_t;

struct Equation {
  I testValue;
  std::vector<I> nums;

  bool isPossible() const {
    assert(not nums.empty());
    if (nums.size() == 1)
      return testValue == nums.front();
    Equation rest;
    rest.testValue = testValue - nums.back();
    rest.nums.assign(nums.begin(), nums.end() - 1);
    if (rest.testValue > 0 && rest.isPossible())
      return true;
    rest.testValue = testValue / nums.back();
    return testValue % nums.back() == 0 && rest.isPossible();
  }

  friend std::istream &operator>>(std::istream &is, Equation &obj) {
    if (is >> obj.testValue) {
      [[maybe_unused]] auto ch = is.get();
      assert(ch == ':');
      std::string line;
      std::getline(is, line);
      assert(is);
      std::istringstream iss(line);
      obj.nums.clear();
      for (I i; iss >> i;)
        obj.nums.push_back(i);
      assert(not obj.nums.empty());
      assert(iss.eof());
    } else
      assert(is.eof());
    return is;
  }
};

// helping std::accumulate
I operator+(I a, Equation const &b) { return a + b.testValue * b.isPossible(); }

void solve2024day7a(std::istream &input) {
  auto b = std::istream_iterator<Equation>{input};

  auto sum = std::accumulate(b, {}, I{});

  std::println("Puzzle answer is {}.", sum);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day7a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
