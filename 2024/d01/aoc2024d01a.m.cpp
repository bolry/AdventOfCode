// https://adventofcode.com/2024/day/1
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
#include <functional>
#include <new>
#include <numeric>
#include <print>
#include <set>

namespace {
    void solve2024day1a(std::istream &input) {
        using LocID = int;

        std::multiset<LocID> leftList, rightList;

        for (LocID leftLocId, rightLocId; input >> leftLocId >> rightLocId;) {
            leftList.insert(leftLocId);
            rightList.insert(rightLocId);
        }

        assert(leftList.size() == rightList.size());
        assert(input.eof());

        auto totDist = std::inner_product(leftList.begin(), leftList.end(), rightList.begin(), std::uintmax_t{},
                                          std::plus<>(), [](LocID a, LocID b) {
                                              return std::abs(a - b);
                                          });

        std::println("Puzzle answer is {}.", totDist);
    }
}

int main(int const argc, char *const argv[]) {
    try {
        assert(argc==2);
        std::ifstream ifs{argv[1]};
        assert(ifs);

        solve2024day1a(ifs);

        return EXIT_SUCCESS;
    } catch (std::bad_alloc const &) {
        std::fputs("Oops, out-of-memory\n", stderr);
    } catch (std::exception const &e) {
        std::println(stderr, "Some standard exception says: `{}'", e.what());
    }
    return EXIT_FAILURE;
}
