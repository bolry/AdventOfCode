#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>

namespace {

char const k_open = '.';
char const k_tree = '|';
char const k_lumberyard = '#';
int const k_width = 50;
int const k_height = 50;
typedef std::array<char, k_width> Row;
typedef std::array<Row, k_height> Land;
int count(Land const &land, char const ch) {
  return std::accumulate(land.begin(),
                         land.end(),
                         0,
                         [ch](int const sum, Row const &row) { return sum + std::count(row.begin(), row.end(), ch); });
}

int count_adjacent(int const x, int const y, Land const &land, char const ch) {
  int sum = 0;
  if (y > 0) {
    auto &above_row = land[y - 1];
    if (x > 0 && above_row[x - 1] == ch) sum++;
    if (above_row[x] == ch) sum++;
    if (x + 1 < above_row.size() && above_row[x + 1] == ch) sum++;
  }
  {
    auto &row = land[y];
    if (x > 0 && row[x - 1] == ch)sum++;
    if (x + 1 < row.size() && row[x + 1] == ch) sum++;
  }
  if (y + 1 < land.size()) {
    auto &lower_row = land[y + 1];
    if (x > 0 && lower_row[x - 1] == ch) sum++;
    if (lower_row[x] == ch) sum++;
    if (x + 1 < lower_row.size() && lower_row[x + 1] == ch) sum++;
  }
  return sum;
}

bool cycle(Land &land) {
  Land const old_land(land);
  for (int y = 0; y < k_height; y++) {
    for (int x = 0; x < k_width; x++) {
      switch (old_land[y][x]) {
        case k_open: if (count_adjacent(x, y, old_land, k_tree) >= 3) land[y][x] = k_tree;
          break;
        case k_tree: if (count_adjacent(x, y, old_land, k_lumberyard) >= 3) land[y][x] = k_lumberyard;
          break;
        case k_lumberyard:
          if (!(count_adjacent(x, y, old_land, k_lumberyard) >= 1
              && count_adjacent(x, y, old_land, k_tree) >= 1))
            land[y][x] = k_open;
          break;
        default:break;
      }
    }
  }
  return old_land == land;
}

void p(Land const &land, int const i) {
  std::cout << "\nAfter  " << i << " minute:\n";
  for (auto &row: land) {
    std::cout << std::string(row.data(), row.size()) << '\n';
  }
}

}  // close anonymous namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("need filename argument");
  std::ifstream in_file(argv[1]);
  if (!in_file) throw std::runtime_error("problem opening file " + std::string(argv[1]));
  Land land;
  for (auto &row : land) {
    in_file.read(row.data(), k_width);
    in_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  if (!in_file) throw std::runtime_error("not enough data in file?");
  p(land, 0);
  for (int i = 0; i < 1000000000; ++i) {
    if (cycle(land)) {
      p(land, i);
      break;
    }
  }
  int const trees = count(land, k_tree);
  int const lumberyards = count(land, k_lumberyard);
  std::cout << "trees: " << trees << " lumberyards: " << lumberyards << " gives resource value of "
            << trees * lumberyards
            << '\n';
  return EXIT_SUCCESS;
}
