#include <array>
#include <cstdlib>
#include <iostream>
#include <utility>

namespace {

typedef std::pair<int, int> Point;
typedef std::array<int, 300 * 300> Grid;

constexpr int hundreds_digit(int const n) {
  return (n / 100) % 10;
}

constexpr int fuel_cell_level(int const x, int const y, int const snr) {
  int const rack_id = x + 10;
  int power_level = rack_id * y;
  power_level += snr;
  power_level *= rack_id;
  power_level = hundreds_digit(power_level);
  return power_level - 5;
}

Grid make_grid(int const snr) {
  Grid grid;
  for (int y = 1; y <= 300; y++)
    for (int x = 1; x <= 300; x++) {
      grid[(x - 1) + (y - 1) * 300] = fuel_cell_level(x, y, snr);
    }
  return grid;
}

int power_square(int const x, int const y, Grid const &grid) {
  int power = 0;
  for (int j = y; j < y + 3; ++j)
    for (int i = x; i < x + 3; ++i)
      power += grid[(i - 1) + (j - 1) * 300];
  return power;
}

Point most_power(Grid const &grid) {
  Point p;
  int best_power = -1000;
  for (int y = 1; y <= 300 - 2; y++)
    for (int x = 1; x <= 300 - 2; x++) {
      int const power = power_square(x, y, grid);
      if (power > best_power) {
        best_power = power;
        p.first = x;
        p.second = y;
      }
    }
  std::cout << "Power: " << best_power << '\n';
  return p;
}

}  // close anonymous namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  Grid grid = make_grid(5235);
  Point location = most_power(grid);
  std::cout << location.first << ',' << location.second << '\n';
  return EXIT_SUCCESS;
}
