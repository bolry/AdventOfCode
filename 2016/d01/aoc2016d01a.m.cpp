// https://adventofcode.com/2016/day/1
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
#include <utility>

namespace {
enum Dir { N, E, S, W };
enum class Turn { Right = 'R', Left = 'L' };

Dir &operator+=(Dir &dir, Turn turn) {
  using enum Turn;
  if (turn == Right) {
    if (dir == Dir::W)
      dir = Dir::N;
    else
      dir = Dir(dir + 1);
  } else if (turn == Left) {
    if (dir == Dir::N)
      dir = Dir::W;
    else
      dir = Dir(dir - 1);
  } else [[unlikely]]
    std::unreachable();
  return dir;
}

void solve2016day1a(std::istream &input) {
  using Coord = int;
  Coord x{}, y{};
  Dir dir{};
  int blocks{};
  char turn{};
  for (char skipComma; input >> turn >> blocks; input >> skipComma) {
    assert(blocks > 0);
    dir += Turn{turn};
    switch (dir) {
    case Dir::N:
      y += blocks;
      break;
    case Dir::E:
      x += blocks;
      break;
    case Dir::S:
      y -= blocks;
      break;
    case Dir::W:
      x -= blocks;
      break;
    [[unlikely]] default:
      std::unreachable();
    }
  }
  assert(input.eof());
  std::println("Puzzle answer is {}", std::abs(x) + std::abs(y));
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2016day1a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
