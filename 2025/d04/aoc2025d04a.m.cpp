#ifdef NDEBUG
#undef NDEBUG
#endif
#ifndef _GLIBCXX_DEBUG
#define _GLIBCXX_DEBUG
#endif
#ifndef _GLIBCXX_DEBUG_PEDANTIC
#define _GLIBCXX_DEBUG_PEDANTIC
#endif
#ifndef _GLIBCXX_ASSERTIONS
#define _GLIBCXX_ASSERTIONS
#endif

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

int main() {
  [[maybe_unused]] constexpr char simp[]{R"(
..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.
)"};
  std::istringstream ifs{simp};
  // std::ifstream ifs{"../input.txt"};
  assert(ifs);
  using Row = std::string;
  std::vector<Row> diagram{std::istream_iterator<Row>{ifs}, {}};
  int const w = static_cast<int>(diagram.size());
  for (auto &row : diagram) {
    row.insert(row.begin(), '\0');
    row.push_back('\0');
  }
  diagram.emplace(diagram.begin(), w + 2u, '\0');
  diagram.emplace_back(w + 2u, '\0');
  // clang-format off
  struct O { int dx, dy; };
  constexpr std::array offsets{
    O{-1, -1}, O{0, -1}, O{1, -1},
    O{-1,  0},           O{1,  0},
    O{-1,  1}, O{0,  1}, O{1,  1},
  };
  // clang-format on
  int sum{};
  for (int y{1}; y != w + 1; ++y)
    for (int x{1}; x != w + 1; ++x)
      if (diagram[y][x] == '@') {
        int neighbors{};
        for (auto const [dx, dy] : offsets)
          neighbors += (diagram[y + dy][x + dx] == '@');
        if (neighbors < 4)
          ++sum;
      }
  std::cout << sum << std::endl;
}
