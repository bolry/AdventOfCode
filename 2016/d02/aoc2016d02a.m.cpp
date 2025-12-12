// https://adventofcode.com/2016/day/2
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

// 1 2 3
// 4 5 6
// 7 8 9

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
};

Button nextButton(std::string_view instructions, Button start) {
  for (auto ch : instructions) {
    switch (ch) {
    case 'U':
      switch (start) {
      case Button::Four:
      case Button::Five:
      case Button::Six:
      case Button::Seven:
      case Button::Eight:
      case Button::Nine:
        start = Button{static_cast<int>(start) - 3};
      }
      break;
    case 'D':
      switch (start) {
      case Button::One:
      case Button::Two:
      case Button::Three:
      case Button::Four:
      case Button::Five:
      case Button::Six:
        start = Button{static_cast<int>(start) + 3};
      }
      break;
    case 'L':
      switch (start) {
      case Button::Two:
      case Button::Three:
      case Button::Five:
      case Button::Six:
      case Button::Eight:
      case Button::Nine:
        start = Button{static_cast<int>(start) - 1};
      }
      break;
    case 'R':
      switch (start) {
      case Button::One:
      case Button::Two:
      case Button::Four:
      case Button::Five:
      case Button::Seven:
      case Button::Eight:
        start = Button{static_cast<int>(start) + 1};
      }
      break;
    }
  }
  return start;
}

void solve2016day2a(std::istream &input) {
  std::string bathroomCode;
  std::string line;
  Button lastButton = Button::Five;
  while (std::getline(input, line)) {
    lastButton = nextButton(line, lastButton);
    bathroomCode += static_cast<char>(lastButton) + '0';
  }
  std::println("Puzzle answer is {}", bathroomCode);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2016day2a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
