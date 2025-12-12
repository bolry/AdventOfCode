// https://adventofcode.com/2024/day/1#part2
// C++23
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <new>
#include <numeric>
#include <print>
#include <unordered_map>

namespace {
  void solve2024day1b(std::istream &input) {
    using LocID = int;

    std::unordered_map<LocID, int> leftList, rightList;

    for (LocID leftLocId, rightLocId; input >> leftLocId >> rightLocId;) {
      ++leftList[leftLocId];
      ++rightList[rightLocId];
    }

    assert(input.eof());

    auto simScore = std::accumulate(leftList.begin(), leftList.end(), std::intmax_t{},
                                    [&](auto acc, auto &x) {
                                      auto [aLeftKey, aLeftCnt] = x;
                                      return acc + aLeftCnt * (aLeftKey * rightList[aLeftKey]);
                                    });

    std::println("Puzzle answer is {}.", simScore);
  }
}

int main(int const argc, char *const argv[]) {
  try {
    assert(argc==2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day1b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
