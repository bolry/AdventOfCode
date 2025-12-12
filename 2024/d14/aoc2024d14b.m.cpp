// https://adventofcode.com/2024/day/14#part2
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
#include <cstdint>
#include <functional>
#include <iterator>
#include <span>
#include <string_view>
#include <vector>

using namespace std::literals::string_view_literals;

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

void pr(std::span<char const, width * tall> map) {
  for (I y{}; y != tall; ++y)
    std::println("{}", std::string_view(map.data() + width * y, width));
}

constexpr auto xes = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"sv;
const std::boyer_moore_searcher xesSearcher(xes.begin(), xes.end());

constexpr bool paintCandidate(std::span<Robot const> robots,
                     std::array<char, width * tall> &map) {
  map.fill(' ');
  for (auto &robot : robots)
    map[robot.py * width + robot.px] = 'X';
  return std::search(map.begin(), map.end(), xesSearcher) != map.end();
}

void solve2024day14b(std::istream &input) {
  std::vector<Robot> robots(std::istream_iterator<Robot>{input}, {});

  std::array<char, width * tall> map;

  for (int i{1};; ++i) {
    moves(robots, 1);
    if (paintCandidate(robots, map)) {
      std::println("vvv After {} seconds vvv", i);
      pr(map);
      std::println("^^^ After {} seconds ^^^", i);
      break;
    }
  }
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day14b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
