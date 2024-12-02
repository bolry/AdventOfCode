// https://adventofcode.com/2024/day/2
// C++23
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iterator>
#include <new>
#include <print>
#include <sstream>
#include <string>
#include <vector>

namespace {
namespace r4s = std::ranges;
using Report = std::vector<int>;

bool isSafe(Report const &report) {
  assert(report.size() > 1);
  if (report[0] == report[1])
    return false;
  bool increasing = report[0] < report[1];
  auto check = [=](auto a, auto b) {
    auto diff = b - a;
    if (increasing)
      return diff < 1 || 3 < diff;
    else
      return diff < -3 || -1 < diff;
  };
  return r4s::adjacent_find(report, check) == report.end();
}

void solve2024day2a(std::istream &input) {
  std::string line;
  int safeReportCnt{};
  Report report;
  report.reserve(8);
  while (std::getline(input, line)) {
    std::istringstream iss(line);
    report.assign(std::istream_iterator<int>{iss}, {});
    if (isSafe(report))
      ++safeReportCnt;
  }
  std::println("Puzzle answer is {}.", safeReportCnt);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day2a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
