// https://adventofcode.com/2024/day/25
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
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {

namespace r4s = std::ranges;
namespace v3s = r4s::views;

using Int = int;
using ColumnHeight = Int;
constexpr ColumnHeight kMaxColHeight{5};
constexpr std::size_t kNrOfColumns{5};
using Columns = std::array<ColumnHeight, kNrOfColumns>;
using Key = Columns;
using Keys = std::vector<Key>;
using Lock = Columns;
using Locks = std::vector<Lock>;

Columns readColumns(std::istream &input) {
  Columns columns{};
  for (ColumnHeight rowCnt{}; rowCnt != kMaxColHeight; ++rowCnt) {
    std::string line;
    std::getline(input, line);
    assert(input and line.size() == columns.size());
    r4s::transform(
        columns, line, columns.begin(),
        [](ColumnHeight colH, char c) { return colH + (c == '#'); });
  }
  return columns;
}

bool readLockOrKey(std::istream &input, Locks &locks, Keys &keys) {
  std::string line;
  input >> line;
  if (not input) {
    assert(input.eof());
    return false;
  }
  assert(line.size() == kNrOfColumns);
  input.ignore(); // remove tailing CR
  bool const isLock = line.find_first_not_of('#') == line.npos;
  using namespace std::literals::string_view_literals;
  assert(isLock or line == "....."sv);
  auto pins = readColumns(input);
  std::getline(input, line);
  assert(isLock and line == "....."sv or line == "#####"sv);
  if (isLock)
    locks.push_back(std::move(pins));
  else
    keys.push_back(std::move(pins));
  return true;
}

void solve2024day25a(std::istream &input) {
  Locks locks;
  Keys keys;

  while (readLockOrKey(input, locks, keys))
    ; // deliberately empty

  assert(not locks.empty());
  assert(not keys.empty());

  Int nrAllColumnsFit{};
  for (auto const &[lock, key] : v3s::cartesian_product(locks, keys))
    nrAllColumnsFit += std::inner_product(
        lock.begin(), lock.end(), key.begin(), Int{1}, std::multiplies<>{},
        [](ColumnHeight colHgtLock, ColumnHeight colHgtKey) -> Int {
          return colHgtLock + colHgtKey <= 5;
        });

  std::println("Puzzle answer is {}.", nrAllColumnsFit);
}

} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day25a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
