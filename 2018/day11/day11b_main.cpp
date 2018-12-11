#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>

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

int power_square(int const x, int const y, int const sz, Grid const &grid) {
  int power = 0;
  for (int j = y; j < y + sz; ++j)
    for (int i = x; i < x + sz; ++i)
      power += grid[(i - 1) + (j - 1) * 300];
  return power;
}

int most_power(int const sz, Grid const &grid) {
  Point p;
  int best_power = -1000;
  for (int y = 1; y <= 300 - (sz - 1); y++)
    for (int x = 1; x <= 300 - (sz - 1); x++) {
      int const power = power_square(x, y,sz, grid);
      if (power > best_power) {
        best_power = power;
        p.first = x;
        p.second = y;
      }
    }
  std::cout << p.first << ',' << p.second <<',' <<sz <<" Power: " << best_power << '\n';
  return best_power;
}

}  // close anonymous namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  Grid grid = make_grid(5235);
  std::array<int,300> powers;
  for(int i = 0; i < 53; i++){
    powers[i] = most_power(i+1, grid);
  }
  auto const pos = std::max_element(powers.begin(), powers.end());
  int const size = std::distance(powers.begin(), pos)+1;
  std::cout << '\n';
  (void)most_power(size,grid);
  return EXIT_SUCCESS;
}
