// https://adventofcode.com/2024/day/6#part2
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

constexpr int sz{130};
using Matrix = std::mdspan<char, std::extents<int, sz, sz>, std::layout_left>;

enum Dir : int { up, down, left, right };

constexpr auto zeroCnt = '.';
constexpr auto endCnt = zeroCnt + 5;

bool move(Dir &dir, int &x, int &y, Matrix &map, bool cnt = true) {
  if (cnt && ++map[x, y] == endCnt)
    return false;
  switch (dir) {
  case up:
    if (y == 0)
      return false;
    if (map[x, y - 1] == '#')
      return move(dir = Dir::right, x, y, map, false);
    --y;
    return true;
  case down:
    if (y == sz - 1)
      return false;
    if (map[x, y + 1] == '#')
      return move(dir = Dir::left, x, y, map, false);
    ++y;
    return true;
  case left:
    if (x == 0)
      return false;
    if (map[(x - 1), y] == '#')
      return move(dir = Dir::up, x, y, map, false);
    --x;
    return true;
  case right:
    if (x == sz - 1)
      return false;
    if (map[(x + 1), y] == '#')
      return move(dir = Dir::down, x, y, map, false);
    ++x;
    return true;
  }
  std::unreachable();
}

void solve2024day6b(std::istream &input) {
  std::string origMap;
  for (std::string row; input >> row;)
    origMap += row;
  assert(origMap.size() == sz * sz);

  auto const guardPos = origMap.find('^');
  assert(guardPos != origMap.npos);
  origMap[guardPos] = zeroCnt;
  int const sx = static_cast<int>(guardPos) % sz;
  int const sy = static_cast<int>(guardPos) / sz;

  int cnt{};
  std::string rawMap;
  for (std::size_t i{}; i != origMap.size(); ++i) {
    if (origMap[i] == '#' || i == guardPos)
      continue;

    rawMap = origMap;
    rawMap[i] = '#';
    Dir dir = Dir::up;
    auto x = sx;
    auto y = sy;
    Matrix map(rawMap.data());
    while (move(dir, x, y, map))
      ; // deliberately empty
    cnt += rawMap.contains(endCnt);
  }

  std::println("Puzzle answer is {}.", cnt);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day6b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
