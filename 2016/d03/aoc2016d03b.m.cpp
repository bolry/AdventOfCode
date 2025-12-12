// https://adventofcode.com/2016/day/3#part2
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

#include <array>

namespace {

struct T {
  std::array<int, 3> s;
  constexpr bool is() const noexcept {
    return s[0] < s[1] + s[2] && s[1] < s[0] + s[2] && s[2] < s[0] + s[1];
  }
};

void solve2016day3b(std::istream &input) {
  std::array<T, 3> t;
  int cnt{};
  while (input >> t[0].s[0] >> t[1].s[0] >> t[2].s[0] >> t[0].s[1] >>
         t[1].s[1] >> t[2].s[1] >> t[0].s[2] >> t[1].s[2] >> t[2].s[2])
    for (auto &tri : t)
      cnt += tri.is();

  std::println("Puzzle answer is {}", cnt);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2016day3b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
