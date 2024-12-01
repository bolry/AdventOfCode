// https://adventofcode.com/2016/day/1#part2
// C++23
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <new>
#include <print>
#include <unordered_set>
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
      dir = static_cast<Dir>(dir + 1);
  } else if (turn == Left) {
    if (dir == Dir::N)
      dir = Dir::W;
    else
      dir = static_cast<Dir>(dir - 1);
  } else [[unlikely]]
    std::unreachable();
  return dir;
}

using Coord = int;
using Pair = std::pair<Coord, Coord>;

struct CoordPairHash {
  std::size_t operator()(Pair const &x) const noexcept {
    return std::hash<std::uint64_t>{}(
        static_cast<std::uint64_t>(x.first) << 32 |
        static_cast<std::uint64_t>(x.second) & 0xFFFF'FFFFu);
  }
};

using Set = std::unordered_set<Pair, CoordPairHash>;

bool done(Coord x, Coord y, Set &been) {
  auto [_, inserted] = been.emplace(x, y);
  if (!inserted) [[unlikely]]
    std::println("Puzzle answer is {}", std::abs(x) + std::abs(y));
  return !inserted;
}

void solve2016day1b(std::istream &input) {
  Coord x{}, y{};
  Set been{{x, y}};
  Dir dir{};
  char turn{};
  for (char skipComma;; input >> skipComma) {
    int blocks{};
    input >> turn >> blocks;
    assert(blocks > 0);
    dir += Turn{turn};
    int dx{}, dy{};
    switch (dir) {
    case Dir::N:
      dy = 1;
      break;
    case Dir::E:
      dx = 1;
      break;
    case Dir::S:
      dy = -1;
      break;
    case Dir::W:
      dx = -1;
      break;
    }
    while (blocks--) [[likely]]
      if (done(x += dx, y += dy, been)) [[unlikely]]
        return;
  }
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2016day1b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
