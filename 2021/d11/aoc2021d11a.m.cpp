#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <numeric>
#include <ranges>

#include <fmt/core.h>
#include <gsl/gsl>

namespace rs = std::ranges;

constexpr int kDim{5};
using Energy = signed char;
using Grid = std::array<Energy, kDim * kDim>;

using fmt::print;

void p(Grid &grid) {
  int i{};
  for (auto c : grid) {
    print("{:x}", c);
    ++i;
    if (i % kDim == 0)
      print("\n");
  }
}

bool flashes(Energy energy) { return energy == Energy{} || energy >= 9; }

int step(Grid &grid) {
  // First, the energy level of each octopus increases by 1.
  rs::for_each(grid, [](auto &c) { ++c; });
  // Then, any octopus with an energy level greater than 9 flashes. This
  // increases the energy level of all adjacent octopuses by 1, including
  // octopuses that are diagonally adjacent. If this causes an octopus to have
  // an energy level greater than 9, it also flashes. This process continues as
  // long as new octopuses keep having their energy level increased beyond 9.
  // (An octopus can only flash at most once per step.)
  for (;;) {
    auto iter{rs::find_if(grid, [](auto val) { return val > Energy{9}; })};
    if (iter != grid.end()) {
      break;
    }
    *iter = Energy{};
    auto idx{std::distance(grid.begin(), iter)};

  }
  // top left corner
  // top line
  // top right corner
  //
  // bottom-left
  // bottom-right
  // side lines
  // centers
  return gsl::narrow_cast<int>(rs::count(grid, Energy{}));
}

int main() {
  std::ifstream ifs{"../input.txt"};
  assert(ifs && "Can't open file");

  Grid grid;
  {
    int idx{};
    for (signed char c; ifs >> c; ++idx)
      grid[idx] = c - '0';
    assert(idx == grid.size());
  }

  int flashes{};
  int steps{};

  while (steps < 1) {
    p(grid);
    ++steps;
    flashes += step(grid);
    assert(flashes == 9);
  }
  print("Flashes after {} steps is {}\n", steps, flashes);
}
