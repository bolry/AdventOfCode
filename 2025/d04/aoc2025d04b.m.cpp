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
  diagram.emplace(diagram.end(), w + 2u, '\0');
  // clang-format off
  struct O { int leftRight, upDown; };
  constexpr std::array offsets{
    O{-1, -1}, O{0, -1}, O{1, -1},
    O{-1,  0},           O{1,  0},
    O{-1,  1}, O{0,  1}, O{1,  1},
  };
  // clang-format on
  int sum{};
  for (auto nextDgram = diagram;; diagram = nextDgram) {
    auto const oldSum = sum;
    for (int row{1}; row != w + 1; ++row)
      for (int col{1}; col != w + 1; ++col)
        if (diagram[row][col] == '@') {
          int neighbors{};
          for (auto const [dx, dy] : offsets)
            neighbors += (diagram[row + dy][col + dx] == '@');
          if (neighbors < 4)
            ++sum, nextDgram[row][col] = '.';
        }
    if (sum == oldSum)
      break;
  }
  std::cout << sum << std::endl;
}
