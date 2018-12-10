#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace {

struct Point {
  int x, y, dx, dy;
};

std::istream &operator>>(std::istream &fin, Point &p) {
  char comma;
  char ignore[12];
  fin.read(ignore, 10) >> p.x >> comma >> p.y;
  fin.read(ignore, 12) >> p.dx >> comma >> p.dy;
  return fin.getline(ignore, 12);
}

std::pair<int, int> skyline(int const timeline, std::vector<Point> const &points, bool const print) {
  if (print) std::cout << "After " << timeline << " seconds:\n";
  auto x_minmax =
      std::minmax_element(points.begin(), points.end(), [](Point const &a, Point const &b) { return a.x < b.x; });
  auto y_minmax =
      std::minmax_element(points.begin(), points.end(), [](Point const &a, Point const &b) { return a.y < b.y; });
  int const width = x_minmax.second->x - x_minmax.first->x + 1;
  int const height = y_minmax.second->y - y_minmax.first->y + 1;
  if (print)
    for (int h = 0; h < height; ++h) {
      std::string row(width, '.');
      for (Point const &p : points) {
        if (p.y - y_minmax.first->y == h) row[p.x - x_minmax.first->x] = '#';
      }
      std::cout << row << '\n';
    }
  return {width, height};
}

void move_points(int const seconds, std::vector<Point> &points) {
  for (auto &p : points) {
    p.x += seconds * p.dx;
    p.y += seconds * p.dy;
  }
}

}  // close anonymous namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2)
    throw std::runtime_error("Need filename argument to program");
  std::ifstream in_file(argv[1]);
  if (!in_file)
    throw std::runtime_error("Problem opening file " + std::string(argv[1]));
  std::istream_iterator<Point> in_reader(in_file);
  std::istream_iterator<Point> in_reader_EOF;
  std::vector<Point> points;
  std::copy(in_reader, in_reader_EOF, std::back_inserter(points));
  std::pair<int, int> smallest(1000000, 1000000);
  std::pair<int, int> minmax;
  int timeline = 0;
  for (;; timeline++) {
    bool smaller = false;
    minmax = skyline(timeline, points, false);
    std::cout << timeline << ' ' << minmax.first << ' ' << minmax.second << '\n';
    if (minmax.first < smallest.first) {
      smallest.first = minmax.first;
      smaller = true;
    }
    if (minmax.second < smallest.second) {
      smallest.second = minmax.second;
      smaller = true;
    }
    if (smaller)
      move_points(1, points);
    else {
      move_points(-1, points);
      skyline(--timeline, points, true);
      break;
    }
  }
  return EXIT_SUCCESS;
}
