// https://adventofcode.com/2024/day/15
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
#include <functional>
#include <mdspan>
#include <string>
#include <string_view>
#include <utility>

using std::swap;

namespace {

using Int = int;

constexpr Int gSz{50};

using Layout = std::layout_left;
using Ext = std::extents<Int, gSz, gSz>;
using Map = std::mdspan<char, Ext, Layout>;
using CMap = std::mdspan<char const, Ext, Layout>;
static_assert(Map::is_always_unique() && Map::is_always_exhaustive() &&
              Map::is_always_strided());

constexpr Int gpsCoord(Int x, Int y) { return 100 * y + x; }

constexpr Int gpsScore(CMap map) {
  static_assert(gSz > 1);
  Int score{};
  for (Int y{1}; y != gSz - 1; ++y)
    for (Int x{1}; x != gSz - 1; ++x)
      if (map[x, y] == 'O')
        score += gpsCoord(x, y);
  return score;
}

void moveRobot(char dir, Map whMap) {
  static constexpr auto dirs = std::invoke([] {
    std::array<std::pair<Int, Int>, std::max({'<', '>', '^', 'v'}) + 1> res{};
    res['<'].first = -1;
    res['>'].first = 1;
    res['^'].second = -1;
    res['v'].second = 1;
    return res;
  });
  auto offset =
      std::string_view(whMap.data_handle(), whMap.size()).find('@', gSz + 1);
  assert(offset != std::string_view::npos);
  Int rx = offset % gSz;
  Int ry = static_cast<Int>(offset / gSz);
  auto [dx, dy] = dirs[dir];
  if (whMap[(rx + dx), ry + dy] == '.')
    std::swap(whMap[rx, ry], whMap[(rx + dx), ry + dy]);
  else if (whMap[(rx + dx), ry + dy] == '#')
    ;
  else if (whMap[(rx + dx), ry + dy] == 'O') {
    int i{2};
    while (whMap[(rx + i * dx), ry + i * dy] == 'O')
      ++i;
    if (whMap[(rx + i * dx), ry + i * dy] == '.') {
      whMap[rx, ry] = '.';
      whMap[(rx + dx), ry + dy] = '@';
      whMap[(rx + i * dx), ry + i * dy] = 'O';
    } else if (whMap[(rx + i * dx), ry + i * dy] == '#')
      ;
    else
      assert(false);
  } else
    assert(false);
}

void solve2024day15a(std::istream &input) {
  std::string warehouse;
  for (std::string row; std::getline(input, row) && not row.empty();)
    warehouse += std::move(row);
  assert(warehouse.size() == gSz * gSz);

  Map warehouseMap{warehouse.data()};

  for (char dir; input >> dir;)
    moveRobot(dir, warehouseMap);
  assert(input.eof());

  auto score = gpsScore(warehouseMap);

  std::println("Puzzle answer is {}.", score);
}

} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day15a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
