// https://adventofcode.com/2024/day/14
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

#include <array>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <span>
#include <vector>

namespace {

using I = std::intmax_t;

constexpr I width{101};
constexpr I tall{103};

struct Robot {
  I px, py;
  I dx, dy;

  friend std::istream &operator>>(std::istream &is, Robot &obj) {
    char c;
    is >> c >> c >> obj.px >> c >> obj.py >> c >> c >> obj.dx >> c >> obj.dy;
    assert(is && c == ',' || is.eof());
    return is;
  }
};

constexpr void moves(Robot &robot, int sec) noexcept {
  robot.px += sec * robot.dx;
  robot.px %= width;
  if (robot.px < 0)
    robot.px += width;
  robot.py += sec * robot.dy;
  robot.py %= tall;
  if (robot.py < 0)
    robot.py += tall;
}

constexpr void moves(std::span<Robot> robots, int sec) noexcept {
  for (auto &robot : robots)
    moves(robot, sec);
}

std::intmax_t safetyFactor(std::span<Robot const> robots) {
  static_assert(width % 2 == 1 && tall % 2 == 1);
  std::array<std::intmax_t, 4> quads{};
  for (auto &robot : robots)
    // is upper-left
    if (robot.px < width / 2 && robot.py < tall / 2)
      ++quads[0];
    // lower-right
    else if (robot.px > width / 2 && robot.py > tall / 2)
      ++quads[3];
    // upper-right
    else if (robot.px > width / 2 && robot.py < tall / 2)
      ++quads[1];
    // lower-left
    else if (robot.px < width / 2 && robot.py > tall / 2)
      ++quads[2];
  return std::accumulate(quads.begin(), quads.end(), std::intmax_t{1},
                         std::multiplies<>{});
}

void solve2024day14a(std::istream &input) {
  std::vector<Robot> robots(std::istream_iterator<Robot>{input}, {});

  moves(robots, 100);

  auto sf = safetyFactor(robots);

  std::println("Puzzle answer is {}.", sf);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day14a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
