// https://adventofcode.com/2024/day/3
// C++23
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <iterator>
#include <new>
#include <numeric>
#include <print>
#include <regex>
#include <string>

namespace {
void solve2024day3a(std::istream &input) {
  std::string in(std::istreambuf_iterator<char>(input), {});
  std::regex regex(R"(mul\((\d{1,3}),(\d{1,3})\))");
  auto first = std::sregex_iterator{in.begin(), in.end(), regex};
  auto last = std::sregex_iterator{};
  auto ip = std::inner_product(
      first, last, first, std::intmax_t{}, std::plus<>{}, [](auto &a, auto &b) {
        return std::stoi(a[1].str()) * std::stoi(b[2].str());
      });
  std::println("Puzzle answer is {}.", ip);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day3a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
