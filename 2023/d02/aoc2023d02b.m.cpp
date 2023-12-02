// https://adventofcode.com/2023/day/2#part2

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>

namespace {

  struct Set {
    int red;
    int green;
    int blue;
  };

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

  constexpr void updateMinSetWith(Set& minSet, Set const& newSet) noexcept {
    minSet.red = std::max(minSet.red, newSet.red);
    minSet.green = std::max(minSet.green, newSet.green);
    minSet.blue = std::max(minSet.blue, newSet.blue);
  }

  constexpr int powerOfSet(Set const& set) noexcept {
    return set.red * set.green * set.blue;
  }
} // namespace

int main([[maybe_unused]] int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);

  assert(argc == 2);
  std::ifstream ifs{argv[1]};
  assert(ifs);

  int powerSum{};

  std::string gameRow;
  while (std::getline(ifs, gameRow)) {
    std::string _; // for ignoring

    int gameId;
    std::istringstream iss{std::move(gameRow)};
    iss >> _ >> gameId >> _; // ignore "Game" and ':'
    assert(iss);

    // std::cout << "Game " << gameId << '\n';

    Set minimumOfSets{};
    while (auto newSet = readSet(iss)) {
      // std::cout << newSet.value() << '\n';
      updateMinSetWith(minimumOfSets, *newSet);
    }

    powerSum += powerOfSet(minimumOfSets);
  }

  std::cout << "Sum of power is " << powerSum << std::endl;

  return EXIT_SUCCESS;
}
