#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace {

struct Cell {
  char c;
  int len1;
  int len2;
};

using Row = std::vector<Cell>;
using Panel = std::vector<Row>;

enum class Direction : char { Up = 'U', Down = 'D', Left = 'L', Right = 'R' };

std::istream &operator>>(std::istream &in, Direction &direction) {
  std::underlying_type_t<Direction> directionIsh;
  if (in >> directionIsh) {
    direction = static_cast<Direction>(directionIsh);
    switch (direction) {
    case Direction::Up:
    case Direction::Down:
    case Direction::Left:
    case Direction::Right:
      break;
    default:
      in.setstate(std::ios_base::failbit);
      break;
    }
  }
  return in;
}

std::istream &ignorePossibleComma(std::istream &in) {
  (in >> std::ws) && (in.peek() == std::char_traits<char>::to_int_type(',')) &&
      in.ignore();
  return in;
}

struct Vector {
  Direction direction;
  int length;

  friend std::istream &operator>>(std::istream &in, Vector &vector) {
    in >> ignorePossibleComma >> vector.direction >> vector.length;
    return in;
  }
};

std::vector<Vector> readVectorLine(std::istream &in) {
  std::string line;
  std::getline(in, line);
  std::istringstream iss{line};
  std::vector<Vector> v;
  std::copy(std::istream_iterator<Vector>{iss}, std::istream_iterator<Vector>{},
            std::back_inserter(v));
  return v;
}

struct PanelInfo {
  int up;
  int down;
  int left;
  int right;
};

PanelInfo getPanelInfo(std::vector<Vector> const &vector) {
  // assuming central port at origin.
  int bestUpper{};
  int bestLower{};
  int bestLeft{};
  int bestRight{};
  int x{};
  int y{};
  for (auto &v : vector) {
    switch (v.direction) {
    case Direction::Up:
      y += v.length;
      bestUpper = std::max(bestUpper, y);
      break;
    case Direction::Down:
      y -= v.length;
      bestLower = std::min(bestLower, y);
      break;
    case Direction::Left:
      x -= v.length;
      bestLeft = std::min(bestLeft, x);
      break;
    case Direction::Right:
      x += v.length;
      bestRight = std::max(bestRight, x);
      break;
    }
  }
  return {
      .up = bestUpper, .down = bestLower, .left = bestLeft, .right = bestRight};
}

void updateCell(char const marker, int const lengthFromOrigin, Cell &cell) {
  cell.c |= marker;
  if (marker == '\1' && cell.len1 == 0) {
    cell.len1 = lengthFromOrigin;
  } else if (marker == '\2' && cell.len2 == 0) {
    cell.len2 = lengthFromOrigin;
  } else {
  }
}
void tracePath(int x, int y, std::vector<Vector> const &paths, Panel &panel,
               char const marker) {
  int stepsFromOrigin{};
  for (auto const &v : paths) {
    switch (v.direction) {
    case Direction::Up:
      for (int i = 0; i != v.length; ++i) {
        ++y;
        ++stepsFromOrigin;
        updateCell(marker, stepsFromOrigin, panel[y][x]);
      }
      break;
    case Direction::Down:
      for (int i = 0; i != v.length; ++i) {
        --y;
        ++stepsFromOrigin;
        updateCell(marker, stepsFromOrigin, panel[y][x]);
      }
      break;
    case Direction::Left:
      for (int i = 0; i != v.length; ++i) {
        --x;
        ++stepsFromOrigin;
        updateCell(marker, stepsFromOrigin, panel[y][x]);
      }
      break;
    case Direction::Right:
      for (int i = 0; i != v.length; ++i) {
        ++x;
        ++stepsFromOrigin;
        updateCell(marker, stepsFromOrigin, panel[y][x]);
      }
      break;
    }
  }
}

std::vector<int> stepDistances(Panel const &panel) {
  std::vector<int> res;
  int const rowMax = panel.size();
  for (int rowIdx = 0; rowIdx != rowMax; ++rowIdx) {
    auto const &row = panel[rowIdx];
    int const colMax = row.size();
    for (int colIdx = 0; colIdx != colMax; ++colIdx) {
      if (auto const &cell = row[colIdx]; cell.c == '\3') {
        res.push_back(cell.len1 + cell.len2);
      }
    }
  }
  return res;
}

} // namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::ios_base::badbit | std::ios_base::eofbit |
                       std::ios_base::failbit);
  if (argc < 2) {
    throw std::runtime_error("need filename argument");
  }
  std::ifstream inFile{argv[1]};
  if (!inFile) {
    throw std::runtime_error("problem opening file " + std::string(argv[1]));
  }
  std::array<std::vector<Vector>, 2> const twoVectors{readVectorLine(inFile),
                                                      readVectorLine(inFile)};

  auto info1 = getPanelInfo(twoVectors[0]);
  auto info2 = getPanelInfo(twoVectors[1]);

  PanelInfo const panelInfo{.up = std::max(info1.up, info2.up),
                            .down = std::min(info1.down, info2.down),
                            .left = std::min(info1.left, info2.left),
                            .right = std::max(info1.right, info2.right)};

  int const width = panelInfo.right - panelInfo.left + 1;
  int const height = panelInfo.up - panelInfo.down + 1;

  Panel panel(height, Row(width));

  int const centralPortX = -panelInfo.left;
  int const centralPortY = -panelInfo.down;

  tracePath(centralPortX, centralPortY, twoVectors[0], panel, '\1');
  tracePath(centralPortX, centralPortY, twoVectors[1], panel, '\2');

  auto const steps = stepDistances(panel);
  std::cout << "Number of crossings " << steps.size() << '\n';

  std::cout << "Shortest number of steps is "
            << *std::min_element(steps.cbegin(), steps.cend()) << '\n'
            << std::flush;

  return EXIT_SUCCESS;
}
