// https://adventofcode.com/2024/day/3#part2
// C++23
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iterator>
#include <new>
#include <print>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>

using namespace std::literals::string_view_literals;

namespace {
void solve2024day3b(std::istream &input) {
  std::string in(std::istreambuf_iterator<char>(input), {});
  std::regex regEx(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
  auto first = std::sregex_iterator{in.begin(), in.end(), regEx};
  auto last = std::sregex_iterator{};
  std::intmax_t ip{};
  bool enable{true};
  for (std::sregex_iterator iter = first; iter != last; ++iter) {
    std::smatch sm = *iter;
    std::string s = sm.str();
    if (s == "do()"sv)
      enable = true;
    else if (s == "don't()"sv)
      enable = false;
    else if (enable)
      ip += std::stoi(sm[1].str()) * std::stoi(sm[2].str());
  }
  std::println("Puzzle answer is {}.", ip);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day3b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
