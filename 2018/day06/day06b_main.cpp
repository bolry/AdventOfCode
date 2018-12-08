#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <new>
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

void CountDistancesManhattanStyle(int x,
                                  int y,
                                  std::vector<Coordinate> const &vector,
                                  std::vector<std::vector<int>> &grid) {
  int & point = grid[y][x];
  for (int coord_id = 0, last = static_cast<int>(vector.size()); coord_id < last; ++coord_id) {
    int const manhattan_dist = std::abs(x - vector[coord_id].x) + std::abs(y - vector[coord_id].y);
    point += manhattan_dist;
  }
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
  std::cout << "\nmin x: " << min_x << " max_x " << max_x << '\n'
            << "min y: " << min_y << " max_y " << max_y << '\n';
  int const width = max_x - min_x + 1;
  int const height = max_y - min_y + 1;
  std::cout << "width: " << width << '\n'
            << "height: " << height << "\n\n";
  for (auto &c : coordinates) c.x -= min_x, c.y -= min_y;
  std::vector<std::vector<int> > grid(height, std::vector<int>(width));
  for (int y = 0; y < height; y++)
    for (int x = 0; x < width; x++)
      CountDistancesManhattanStyle(x, y, coordinates, grid);
  int freq = 0;
  for (auto const &row : grid) {
    for (auto const dot : row) {
      if(dot < 10000) freq++;
    }
  }
  std::cout << "Day 6 B region size is " << freq << '\n';
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
