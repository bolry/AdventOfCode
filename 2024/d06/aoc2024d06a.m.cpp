// https://adventofcode.com/2024/day/6
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
#include <mdspan>
#include <string>
#include <utility>

namespace {

namespace r4s = std::ranges;

constexpr int sz{130};
using Matrix = std::mdspan<char, std::extents<int, sz, sz>, std::layout_left>;

enum Dir : int { up, down, left, right };

bool move(Dir &dir, int &x, int &y, Matrix &map) {
  map[x, y] = 'X';
  switch (dir) {
  case up:
    if (y == 0)
      return false;
    if (map[x, y - 1] == '#')
      dir = Dir::right;
    else
      --y;
    return true;
  case down:
    if (y == sz - 1)
      return false;
    if (map[x, y + 1] == '#')
      dir = Dir::left;
    else
      ++y;
    return true;
  case left:
    if (x == 0)
      return false;
    if (map[(x - 1), y] == '#')
      dir = Dir::up;
    else
      --x;
    return true;
  case right:
    if (x == sz - 1)
      return false;
    if (map[(x + 1), y] == '#')
      dir = Dir::down;
    else
      ++x;
    return true;
  }
  std::unreachable();
}

void solve2024day6a(std::istream &input) {
  std::string rawMap;
  for (std::string row; input >> row;)
    rawMap += row;
  assert(rawMap.size() == sz * sz);
  Matrix map(rawMap.data());

  // find start
  auto z = rawMap.find('^');
  Dir dir = Dir::up;
  // assert(z == 64);
  int x = static_cast<int>(z) % sz;
  int y = static_cast<int>(z) / sz;
  // assert(x == 4);
  // assert(y == 6);

  while (move(dir, x, y, map))
    ; // Deliberately empty

  auto cnt = r4s::count(rawMap, 'X');

  std::println("Puzzle answer is {}.", cnt);
}

} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day6a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
