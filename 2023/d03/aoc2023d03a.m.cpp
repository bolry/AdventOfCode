// https://adventofcode.com/2023/day/3

#include <cstdlib>
#include <string>
#include <cctype>
#include <cassert>
#include <fstream>
#include <charconv>
#include <utility>
#include <vector>
#include <string_view>
#include <iostream>

namespace {
  constexpr auto p{'.'};

  constexpr bool isDigit(char c) noexcept { return std::isdigit(static_cast<unsigned char>(c)); }

  constexpr bool isValid(std::vector<std::string> const& schematic, std::size_t row, char const* first,
                         const char* last) noexcept {
    auto const len = (last - first) + 2;
    constexpr std::string_view kStuff{".1234567890"};
    constexpr auto npos = std::string_view::npos;
    // above
    {
      auto const& aboveRow = schematic[row - 1];
      auto const start = aboveRow.data() + (first - (schematic[row].data() + 1));
      std::string_view above{start, len};
      if (above.find_first_not_of(kStuff) != npos) return true;
    }
    // below
    {
      auto const& belowRow = schematic[row + 1];
      auto const start = belowRow.data() + (first - (schematic[row].data() + 1));
      std::string_view below{start, len};
      if (below.find_first_not_of(kStuff) != npos) return {true};
    }
    // left
    if (kStuff.find(*(first - 1)) == npos) return {true};
    // rigth
    return {kStuff.find(*last) == npos};
  }
} // namespace


int main([[maybe_unused]] int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);

  assert(argc == 2);
  std::ifstream ifs{argv[1]};
  assert(ifs);

  std::vector<std::string> engineSchematic;
  engineSchematic.reserve(142);
  engineSchematic.emplace_back(); // extra row before

  for (std::string tmp; std::getline(ifs, tmp);) {
    std::string row(1, p);
    row.reserve(tmp.size() + 2);
    row += tmp;
    row += p;
    engineSchematic.push_back(std::move(row));
  }
  ifs.close();
  auto const n = engineSchematic.back().size();
  engineSchematic.emplace_back(n, p); // extra row at end
  engineSchematic[0].assign(n, p); // first extra row, now know length
  assert(engineSchematic.size() == n);

  int sumPartNumbers{};

  for (std::size_t y{1}, endY{engineSchematic.size() - 1}; y != endY; ++y) {
    auto const& row = engineSchematic[y];
    auto const* first = row.data() + 1; // adjusting for extra period in beginning
    auto const* last = first + (row.size() - 2); // adjusting for extra period at end
    while (first != last) {
      while (not isDigit(*first) && ++first != last) {
      }
      int num{};
      auto [ptr,ec] = std::from_chars(first, last, num);
      if (ec == std::errc{}) [[likely]]
      {
        assert(num != 0);
        if (isValid(engineSchematic, y, first, ptr)) {
          sumPartNumbers += num;
          std::cout << num << std::endl;
        }
        first = ptr;
      } else
        assert(ec == std::errc::invalid_argument);
    }
  }

  std::cout << "Sum or part numbers " << sumPartNumbers << '.' << std::endl;
  return EXIT_SUCCESS;
}
