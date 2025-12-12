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
#include <charconv>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <numeric>
#include <print>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {
constexpr auto prDebug = true;

using Int = std::int_least64_t;

Int stoInt(std::string_view const str) {
  Int res;
  auto const [p, ec] =
      std::from_chars(str.data(), str.data() + str.size(), res);
  assert((ec == std::errc{}) && (p == (str.data() + str.size())));
  return res;
}

std::vector<Int> getNumbers(std::span<std::string const> const hw,
                            std::size_t const colStart,
                            std::size_t const colEnd) {
  std::vector<Int> res;
  for (std::size_t col{colStart}; col <= colEnd; ++col) {
    std::string nrStr;
    for (auto const &row : hw)
      if (row[col] != ' ')
        nrStr += row[col];
    res.push_back(stoInt(nrStr));
  }
  return res;
}
} // namespace
int main() {
  [[maybe_unused]] constexpr char simp[]{"123 328  51 64 \n"
                                         " 45 64  387 23 \n"
                                         "  6 98  215 314\n"
                                         "*   +   *   +  \n"};
  // std::istringstream in{simp};
  std::ifstream in{"../input.txt"};
  assert(in);
  std::string ops;
  std::vector<std::string> hw; // homework
  while (std::getline(in, ops)) {
    assert(not ops.empty());
    if (ops.front() == '+' || ops.front() == '*')
      break; // last line of numbers
    hw.push_back(std::move(ops));
  }
  assert(in);

  std::vector<std::size_t> offsets;
  for (std::size_t idx{}; idx != ops.size(); ++idx) {
    if (ops[idx] == '+' || ops[idx] == '*')
      offsets.push_back(idx);
    else
      assert(ops[idx] == ' ');
  }

  for (auto const x = ops.size(); auto const &row : hw)
    assert(x == row.size());
  Int sum{};
  for (auto b = offsets.begin(), e = offsets.end(); b != e; ++b) {
    auto nxt = std::next(b);
    auto colEndOffset = (nxt != e) ? (*nxt - 2u) : (ops.size() - 1u);
    auto const numbers = getNumbers(hw, *b, colEndOffset);
    if (ops[*b] == '+') {
      Int addResult = std::reduce(numbers.begin(), numbers.end());
      if constexpr (prDebug) {
        for (auto const nr : numbers)
          std::cout << " + " << nr;
        std::cout << " = " << addResult << '\n';
      }
      sum += addResult;
    } else if (ops[*b] == '*') {
      Int mulResult = std::reduce(numbers.begin(), numbers.end(), Int{1u},
                                  std::multiplies<>());
      if constexpr (prDebug) {
        for (auto const nr : numbers)
          std::cout << " * " << nr;
        std::cout << " = " << mulResult << '\n';
      }
      sum += mulResult;
    } else
      assert(false);
  }
  std::cout << sum << std::endl;
}
