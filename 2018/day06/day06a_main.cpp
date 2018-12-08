#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <new>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace {
struct Coordinate {
  int x;
  int y;

  friend std::ostream &operator<<(std::ostream &os, Coordinate const &coordinate) {
    return os << "x: " << coordinate.x << " y: " << coordinate.y;
  }
};
std::istream &operator>>(std::istream &is, Coordinate &coordinate) {
  char comma_ignore;
  return is >> coordinate.x >> comma_ignore >> coordinate.y;
}

void findClosestPoint(int x, int y, std::vector<Coordinate> const &vector, std::vector<std::vector<int>> &grid) {
  int shortest = 10000;
  int best_id = -1;
  for (int coord_id = 0, last = static_cast<int>(vector.size()); coord_id < last; ++coord_id) {
    int manhattan_dist = std::abs(x - vector[coord_id].x) + std::abs(y - vector[coord_id].y);
    if (manhattan_dist < shortest) {
      shortest = manhattan_dist;
      best_id = coord_id;
    } else if (manhattan_dist == shortest) {
      best_id = -1;
    }
  }
  grid[y][x] = best_id;
}

}

int main(int argc, char *argv[])
try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("Need input data filename\n");
  std::ifstream coordinate_file(argv[1]);
  if (!coordinate_file) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
  std::vector<Coordinate> coordinates;
  std::istream_iterator<Coordinate> coord_reader(coordinate_file);
  std::istream_iterator<Coordinate> coord_reader_EOF;
  std::copy(coord_reader, coord_reader_EOF, std::back_inserter(coordinates));
  int const min_x = [](std::vector<Coordinate> const &vc) {
    int m = 1000;
    for (auto const &c : vc) m = std::min(m, c.x);
    return m;
  }(coordinates);
  int const max_x = [](std::vector<Coordinate> const &vc) {
    int m = -1;
    for (auto const &c : vc) m = std::max(m, c.x);
    return m;
  }(coordinates);
  int const min_y = [](std::vector<Coordinate> const &vc) {
    int m = 1000;
    for (auto const &c:vc) m = std::min(m, c.y);
    return m;
  }(coordinates);
  int const max_y = [](std::vector<Coordinate> const &vc) {
    int m = -1;
    for (auto const &c : vc) m = std::max(m, c.y);
    return m;
  }(coordinates);
  std::copy(coordinates.begin(), coordinates.end(), std::ostream_iterator<Coordinate>(std::cout, "\n"));
  std::cout << "\nmin x: " << min_x << " max_x " << max_x << '\n'
            << "min y: " << min_y << " max_y " << max_y << '\n';
  int const width = max_x - min_x + 1;
  int const height = max_y - min_y + 1;
  std::cout << "width: " << width << '\n'
            << "height: " << height << "\n\n";
  for (auto &c : coordinates) c.x -= min_x, c.y -= min_y;
  std::copy(coordinates.begin(), coordinates.end(), std::ostream_iterator<Coordinate>(std::cout, "\n"));
  std::vector<std::vector<int> > grid(height, std::vector<int>(width));
  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
      findClosestPoint(x, y, coordinates, grid);
  std::vector<int> freq(coordinates.size()+1);
  for (auto const &row : grid) {
    for (auto const dot : row) {
      std::cout << dot << " ";
      freq[dot+1]++;
    }
    std::cout << '\n';
  }
  std::set<int> infinity_list;
  infinity_list.insert(grid.front().begin(), grid.front().end());
  infinity_list.insert(grid.back().begin(), grid.back().end());
  for (int y = 1, max_y = static_cast<int>(grid.size()) - 1; y < max_y; y++) {
    infinity_list.insert(grid[y].front());
    infinity_list.insert(grid[y].back());
  }
  for( int black_listed: infinity_list){
    freq[black_listed+1] = -1;
  }
  auto winner_pos= std::max_element(freq.begin(), freq.end());
  std::cout << "Day 6 A result " << *winner_pos << " at coordinate " << std::distance(freq.begin(), winner_pos) << '\n';
  return EXIT_SUCCESS;
}
catch (std::bad_alloc const &) {
  std::fputs("Sorry, out-of-memory\n", stderr);
  std::fflush(stderr);
  return EXIT_FAILURE;
}
catch (std::exception const &x) {
  std::cerr << x.what() << '\n' << std::flush;
  return EXIT_FAILURE;
}
#if 0
catch (...) {
    std::cerr << "Unexpected unhandled error\n" << std::flush;
    return EXIT_FAILURE;
}
#endif  // 0
