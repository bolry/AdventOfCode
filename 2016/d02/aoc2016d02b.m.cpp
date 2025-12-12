// https://adventofcode.com/2016/day/2#part2
// C++23
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <new>
#include <print>

#include <string>
#include <string_view>

namespace {

//     1
//   2 3 4
// 5 6 7 8 9
//   A B C
//     D

enum class Button {
  One = 1,
  Two = 2,
  Three = 3,
  Four = 4,
  Five = 5,
  Six = 6,
  Seven = 7,
  Eight = 8,
  Nine = 9,
  A = 10,
  B = 11,
  C = 12,
  D = 13,
};

Button nextButton(std::string_view instructions, Button start) {
  for (auto ch : instructions) {
    switch (ch) {
    case 'U':
      switch (start) {
      case Button::Three:
      case Button::D:
        start = Button{static_cast<int>(start) - 2};
        break;
      case Button::Six:
      case Button::Seven:
      case Button::Eight:
      case Button::A:
      case Button::B:
      case Button::C:
        start = Button{static_cast<int>(start) - 4};
        break;
      }
      break;
    case 'D':
      switch (start) {
      case Button::One:
      case Button::B:
        start = Button{static_cast<int>(start) + 2};
        break;
      case Button::Two:
      case Button::Three:
      case Button::Four:
      case Button::Six:
      case Button::Seven:
      case Button::Eight:
        start = Button{static_cast<int>(start) + 4};
        break;
      }
      break;
    case 'L':
      switch (start) {
      case Button::Three:
      case Button::Four:
      case Button::Six:
      case Button::Seven:
      case Button::Eight:
      case Button::Nine:
      case Button::B:
      case Button::C:
        start = Button{static_cast<int>(start) - 1};
      }
      break;
    case 'R':
      switch (start) {
      case Button::Two:
      case Button::Three:
      case Button::Five:
      case Button::Six:
      case Button::Seven:
      case Button::Eight:
      case Button::A:
      case Button::B:
        start = Button{static_cast<int>(start) + 1};
      }
      break;
    }
  }
  return start;
}

void solve2016day2b(std::istream &input) {
  std::string bathroomCode;
  std::string line;
  Button lastButton = Button::Five;
  while (std::getline(input, line)) {
    lastButton = nextButton(line, lastButton);
    char ch = static_cast<char>(lastButton);
    if ('\x1' <= ch && ch <= '\x9')
      bathroomCode += static_cast<char>(lastButton) + '0';
    else if ('\xA' <= ch && ch <= '\xD')
      bathroomCode += static_cast<char>(lastButton) - '\xA' + 'A';
    else
      assert(false);
  }
  std::println("Puzzle answer is {}", bathroomCode);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2016day2b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
