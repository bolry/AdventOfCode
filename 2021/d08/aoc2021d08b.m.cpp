#include <algorithm>
#include <array>
#include <fstream>
#include <istream>
#include <iterator>
#include <limits>
#include <numeric>
#include <string>
#include <string_view>

#include <fmt/core.h>
#include <gsl/gsl>

namespace rs = std::ranges;
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

const std::array kLookup{
    "abcefg"sv,  // 0
    "cf"sv,      // 1
    "acdeg"sv,   // 2
    "acdfg"sv,   // 3
    "bcdf"sv,    // 4
    "abdfg"sv,   // 5
    "abdefg"sv,  // 6
    "acf"sv,     // 7
    "abcdefg"sv, // 8
    "abcdfg"sv,  // 9
};

std::array<std::string, kLookup.size()> sevenSegmentedDisplays;
auto const &kSsd = sevenSegmentedDisplays; // sorted version of kLookup

struct Line {
  std::array<std::string, 10> raws;
  std::array<std::string, 4> vals;
};

std::istream &operator>>(std::istream &in, Line &line) {
  for (auto &raw : line.raws)
    in >> raw;
  in.ignore(std::numeric_limits<std::streamsize>::max(), '|');
  for (auto &val : line.vals)
    in >> val;
  return in;
}

bool mapsOK(std::array<std::string, 10> raws, std::string_view key) {
  for (auto &str : raws) {
    for (auto &ch : str)
      ch = key[ch - 'a'];
    rs::sort(str);
  }
  rs::sort(raws);
  return raws == kSsd;
}

std::string decodeRaws(std::array<std::string, 10> const &raws) {
  auto possibleKey{"abcdefg"s};
  while (!mapsOK(raws, possibleKey))
    rs::next_permutation(possibleKey);
  return possibleKey;
}

int getDigit(std::string str, std::string_view key) {
  for (auto &ch : str)
    ch = key[ch - 'a'];
  rs::sort(str);
  return gsl::narrow_cast<int>(
      std::distance(kLookup.begin(), rs::find(kLookup, str)));
}

int getValue(Line const &line) {
  auto key{decodeRaws(line.raws)};
  return 1000 * getDigit(line.vals[0], key) +
         100 * getDigit(line.vals[1], key) + 10 * getDigit(line.vals[2], key) +
         1 * getDigit(line.vals[3], key);
}

int main() {
  rs::partial_sort_copy(kLookup, sevenSegmentedDisplays);
  std::ifstream ifs{"../input.txt"};
  assert(ifs && "Can't open file");
  auto sum{
      std::accumulate(std::istream_iterator<Line>{ifs}, {}, 0,
                      [](int a, auto const &b) { return a + getValue(b); })};
  fmt::print("The sum is {}\n", sum);
}
