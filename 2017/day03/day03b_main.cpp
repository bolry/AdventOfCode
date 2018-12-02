#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <new>
#include <vector>

constexpr int const input = 277678;

enum class Step {
  right, up, left, down
};

int main() try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);

  std::vector<int> memory{0, 1};

  Step dir = Step::right;
  int width = 0;
  int x_offset = 0;
  int y_offset = 0;
  int square = 1;
  while (memory[square] <= input) {
    square++;
    int new_value = memory[square - 1];  // add previous square
    switch (dir) {
      case Step::right:x_offset++;
        // look left already done
        if (y_offset < 0)
          if (width + x_offset != 1)  // look up-left
            new_value += memory[square + y_offset * 8];
          else
            new_value += memory[square - 2];
        if (x_offset < width)
          new_value += memory[square + y_offset * 8 + 2];  // look up-right
        if (x_offset > width) {
          ++width;
          dir = Step::up;
        } else
          new_value += memory[square + y_offset * 8 + 1];  // look up
        break;
      case Step::up:y_offset++;
        // look down already done
        if (width + y_offset != 2)  // look down-left
          new_value += memory[square - (x_offset - 1) * 8 - 2];
        else
          new_value += memory[square - 2];
        if (y_offset < width - 1)
          new_value += memory[square - (x_offset - 1) * 8]; // look up-left
        if (y_offset == width)
          dir = Step::left;
        else
          new_value += memory[square - (x_offset - 1) * 8 - 1];  // look left
        break;
      case Step::left:x_offset--;
        // look right already done
        if (width - x_offset != 1)  // look down-right
          new_value += memory[square - (y_offset - 1) * 8 - 4];
        else
          new_value += memory[square - 2];
        if (x_offset > 1 - width)
          new_value += memory[square - (y_offset - 1) * 8 - 2];  // look down-left
        if (x_offset == -width)
          dir = Step::down;
        else
          new_value += memory[square - (y_offset - 1) * 8 - 3];  // look down
        break;
      case Step::down:--y_offset;
        // look up already done
        if (width - y_offset != 1)  // look up-right
          new_value += memory[square + (x_offset + 1) * 8 - 6];
        else
          new_value += memory[square - 2];
        if (y_offset > 1 - width)
          new_value += memory[square + (x_offset + 1) * 8 - 4];  // look down-right
        if (y_offset == -width)
          dir = Step::right;
        else
          new_value += memory[square + (x_offset + 1) * 8 - 5];  // look right
        break;
    }
    memory.push_back(new_value);
  }
  std::cout << "First value larger than " << input << " is "
            << memory[square] << " at square " << square << '\n';
  return EXIT_SUCCESS;
}
catch (std::bad_alloc const &) {
  std::fputs("Sorry, ran out-of-memory\n", stderr);
  std::fflush(stderr);
  return EXIT_FAILURE;
}
catch (std::exception const &x) {
  std::cerr << x.what() << '\n' << std::flush;
  return EXIT_FAILURE;
}
