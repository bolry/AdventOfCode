// https://adventofcode.com/2024/day/4#part2
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

#include <mdspan>
#include <string>

namespace {

constexpr int sz{140};
using Matrix = std::mdspan<char, std::extents<int, sz, sz>, std::layout_left>;

void solve2024day4b(std::istream &input) {
  std::string rawWords;
  for (std::string row; input >> row;)
    rawWords += row;
  assert(rawWords.size() == sz * sz);

  Matrix words{rawWords.data()};

  int wrdCnt{};

  for (int y{}; y < sz - 2; ++y)
    for (int x{}; x < sz - 2; ++x)
      if (words[x + 1, y + 1] == 'A')
        if (words[x, y] == 'M' && words[x + 2, y + 2] == 'S' ||
            words[x, y] == 'S' && words[x + 2, y + 2] == 'M')
          if (words[x + 2, y] == 'M' && words[x, y + 2] == 'S' ||
              words[x + 2, y] == 'S' && words[x, y + 2] == 'M')
            ++wrdCnt;

  std::println("Puzzle answer is {}.", wrdCnt);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day4b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
