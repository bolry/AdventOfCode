#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

struct Pair {
  int x;
  int y;

  friend std::ostream &operator<<(std::ostream &os, Pair const &pair) {
    os << "x: " << pair.x << " y: " << pair.y;
    return os;
  }

  friend std::istream &operator>>(std::istream &os, Pair &pair) {
    os >> pair.x;
    os.ignore(); // comma
    os >> pair.y;
    return os;
  }
};

constexpr auto until{std::numeric_limits<std::streamsize>::max()};
constexpr auto space{' '};

int main() {
  std::ifstream ifs{"../input.txt"};
  assert(ifs && "can't open the file");
  // read coordinates
  for (Pair pair{}; ifs >> pair;)
    std::cout << pair << '\n';
  ifs.clear();
  // read fold instructions
  for (bool firstTime{true}; firstTime; firstTime = true) {
    // E.g., "fold along y=7\n"
    ifs.ignore(until, space); // fold
    ifs.ignore(until, space); // along
    char xOrY;
    ifs >> xOrY;
    ifs.ignore(); // equal sign
    int val;
    ifs >> val;
    if (!ifs)
      break;
    assert(xOrY == 'x' || xOrY == 'y');
    std::cout << xOrY << " = " << val << '\n';
  }
  return 33;
}
