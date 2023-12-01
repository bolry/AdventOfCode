// https://adventofcode.com/2023/day/1#part2

#include <array>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>  // where some algorithms go to hide
#include <string>
#include <string_view>

namespace {
  struct WordToNum {
    std::string_view word;
    int num;
  };

  constexpr std::array<WordToNum, 9> kWordToNum{
    {
      {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
    }
  };
  constexpr std::string_view kDigits{"1234567890"};
  constexpr auto npos = std::string_view::npos;

  constexpr int firstDigit(std::string_view const line) noexcept {
    auto firstPos = npos;
    int value{};
    if (auto const pos = line.find_first_of(kDigits); pos != npos) [[likely]]
      firstPos = pos, value = {line[pos] - '0'};
    if (firstPos != 0) // optimization
      for (auto const& [word, num]: kWordToNum)
        if (auto const pos = line.substr(0, firstPos != npos ? firstPos + 1 : npos).find(word); pos < firstPos)
          firstPos = pos, value = {num};
    assert(value);
    return value;
  }

  constexpr int lastDigit(std::string_view const line) noexcept {
    auto lastPos = decltype(npos){};
    int value{};
    if (auto const pos = line.find_last_of(kDigits); pos != npos) [[likely]]
      lastPos = pos, value = {line[pos] - '0'};
    if (lastPos != line.size() - 1u) // optimization
      for (auto const& [word, num]: kWordToNum)
        if (auto pos = line.substr(lastPos).rfind(word); pos != npos)
          if (pos += lastPos; pos > lastPos)
            lastPos = pos, value = {num};
    assert(value);
    return value;
  }

  constexpr int calibrationValue(std::string_view const line) noexcept {
    return firstDigit(line) * 10 + lastDigit(line);
  }
}

int main([[maybe_unused]] int const argc, char* const argv[]) {
  std::ios_base::sync_with_stdio(false);

  assert(argc==2);
  std::ifstream ifs{argv[1]};
  assert(ifs);

  auto const sum = std::accumulate(std::istream_iterator<std::string>{ifs}, {}, 0,
                                   [](int const acc, std::string_view const line) {
                                     return acc + calibrationValue(line);
                                   });

  std::cout << "The total sum of all calibration values is " << sum << '.' << std::endl;

  return EXIT_SUCCESS;
}
