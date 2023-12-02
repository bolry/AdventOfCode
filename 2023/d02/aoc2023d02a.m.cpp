// https://adventofcode.com/2023/day/2

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace {
  struct Set {
    int red;
    int green;
    int blue;
  };

  constexpr bool operator<=(Set const& a, Set const& b) noexcept {
    return a.red <= b.red && a.green <= b.green && a.blue <= b.blue;
  }

  [[maybe_unused]] std::ostream& operator<<(std::ostream& os, Set const& obj) {
     os << "red: " << obj.red << " green: " << obj.green
           << " blue: " << obj.blue;
    return os;
  }

  std::optional<Set> readSet(std::istream& iss) {
    Set set{};

    int num;
    std::string color;
    while (iss >> num >> color) {
      bool isLastSet{};
      bool moreValuesInSet{};

      if (auto const lastChar = color.back(); lastChar == ';')
        color.pop_back(), isLastSet = {true};
      else if (lastChar == ',')
        color.pop_back(), moreValuesInSet = {true};
      else {
        // deliberatly empty
      }

      if (auto const firstChar = color.front(); firstChar == 'r') {
        assert(color == "red");
        assert(set.red == 0);
        set.red = {num};
      } else if (firstChar == 'g') {
        assert(color == "green");
        assert(set.green == 0);
        set.green = {num};
      } else {
        assert(color == "blue");
        assert(set.blue == 0);
        set.blue = {num};
      }

      if (isLastSet || not moreValuesInSet) return {set};
    }
    return std::nullopt;
  }

  constexpr bool isPossible(Set const& set) noexcept {
    constexpr Set gameBag{.red = 12, .green = 13, .blue = 14};
    return set <= gameBag;
  }
} // namespace

int main([[maybe_unused]] int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);

  assert(argc == 2);
  std::ifstream ifs{argv[1]};
  assert(ifs);

  int sumGameIds{};

  std::string gameRow;
  while (std::getline(ifs, gameRow)) {
    std::istringstream iss{std::move(gameRow)};

    int gameId;

    std::string _; // for ignoring
    iss >> _ >> gameId >> _; // ignore "Game" and ':'
    assert(iss);

    // std::cout << "Game " << gameId << '\n';
    bool gamePossible{true};
    while (auto newSet = readSet(iss)) {
      //  std::cout << newSet.value() << '\n';
      if (not isPossible(*newSet)) gamePossible = {false};
    }
    if (gamePossible) sumGameIds += gameId;
  }
  std::cout << "The total sum of the IDs for the specified games is " << sumGameIds << '.' << std::endl;
  return EXIT_SUCCESS;
}
