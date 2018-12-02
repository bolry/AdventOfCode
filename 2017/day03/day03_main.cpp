#include <cmath>
#include <cstdlib>
#include <iostream>

namespace {

enum class Step {
  right, up, left, down
};

constexpr int const input = 277678;

}  // close anonymous namespace

int main() try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  Step dir = Step::right;
  int width = 0;
  int x_offset = 0;
  int y_offset = 0;
  int square = 1;
  for (; square < input; square++) {
    switch (dir) {
      case Step::right:
        if (++x_offset > width) {
          ++width;
          dir = Step::up;
        }
        break;
      case Step::up: if (++y_offset == width) dir = Step::left;
        break;
      case Step::left: if (--x_offset == -width) dir = Step::down;
        break;
      case Step::down: if (--y_offset == -width)dir = Step::right;
        break;
    }
  }
  std::cout << "Manhattan distance for " << input << " is "
            << std::abs(x_offset) + std::abs(y_offset) << '\n';
}
catch (std::bad_alloc const &) {
  std::fputs("Sorry, out-of-memory\n", stderr);
  std::fflush(stderr);
}
catch (std::exception const &x) {
  std::cerr << x.what() << '\n' << std::flush;
}
