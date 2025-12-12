// https://adventofcode.com/2016/day/3
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
#include <array>

namespace {

struct T {
  std::array<int, 3> s;
  constexpr bool is() const noexcept {
    return s[0] < s[1] + s[2] && s[1] < s[0] + s[2] && s[2] < s[0] + s[1];
  }

  friend std::istream &operator>>(std::istream &is, T &t) {
    is >> t.s[0] >> t.s[1] >> t.s[2];
    return is;
  }
};

void solve2016day3a(std::istream &input) {
  auto i = std::istream_iterator<T>{input};
  std::println("Puzzle answer is {}",
               std::count_if(i, {}, [](auto &t) { return t.is(); }));
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2016day3a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
