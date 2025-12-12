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

#include <cassert>
#include <cstdint>
#include <fstream>
#include <print>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace {
  constexpr auto prDebug = true;

  using Int = std::int_least64_t;
} // namespace
int main() {
  [[maybe_unused]] constexpr char simp[]{
    R"END_DATA(123 328  51 64
 45 64  387 23
  6 98  215 314
*   +   *   +
)END_DATA"
  };
  std::istringstream in{simp};
  // std::ifstream in{"../input.txt"};
  assert(in);
  std::string line;
  using Row = std::vector<Int>;
  std::vector<Row> hw; // homework
  while (std::getline(in, line)) {
    assert(not line.empty());
    if (line.front() == '+' || line.front() == '*')
      break; // last line
    std::istringstream numStream{line};
    using IntIter = std::istream_iterator<Int>;
    hw.emplace_back(IntIter{numStream}, IntIter{});
  }
  assert(in);
  assert(not hw.empty());
  auto const nrRows{hw.size()};
  auto const nrCols{hw.front().size()};
  for (auto const &row: hw)
    assert(nrCols == row.size());
  Int sum{};
  std::istringstream opStream{line};
  std::vector ops(std::istream_iterator<char>{opStream}, {});
  assert(ops.size() == nrCols);
  for (std::size_t col{}; col != nrCols; ++col) {
    if (char const op = ops[col]; op == '+') {
      Int addResult{};
      for (std::size_t row{}; row != nrRows; ++row) {
        if constexpr (prDebug)
          std::print(" + {}", hw[row][col]);
        addResult += hw[row][col];
      }
      if constexpr (prDebug)
        std::println(" = {}", addResult);
      sum += addResult;
    } else if (op == '*') {
      Int mulResult{1};
      for (std::size_t row{}; row != nrRows; ++row) {
        if constexpr (prDebug)
          std::print(" * {}", hw[row][col]);
        mulResult *= hw[row][col];
      }
      if constexpr (prDebug)
        std::println(" = {}", mulResult);
      sum += mulResult;
    } else
      assert(false);
  }
  std::println("{}", sum);
}
