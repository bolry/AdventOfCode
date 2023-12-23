// https://adventofcode.com/2023/day/21

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

// namespace {
namespace r4s = std::ranges;
using InIter = std::istream_iterator<std::string>;
using U = std::string::size_type;
// }  // anonymous namespace

int main([[maybe_unused]] int argc, char* argv[]) {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    std::vector<std::string> map(InIter{ifs}, {});
    U const yStart = {map.size() / 2u};
    U const xStart = {map.front().size() / 2u};
    [[maybe_unused]] auto oldValue = std::exchange(map[yStart][xStart], '.');
    assert(oldValue == 'S');
    std::cout << "Start at x = " << xStart << ", y = " << yStart << '\n';
    auto const rocks = map;
    map[yStart][xStart] = 'O';
    auto nextMap = rocks;
    for (int stepsLeft{64}; stepsLeft != 0; --stepsLeft) {
        nextMap = rocks;
        for (U y{}; y != map.size(); ++y) {
            auto& row = map[y];
            for (U x{}; x != row.size(); ++x) {
                if (row[x] == 'O') {
                    auto updateIfNotRock = [](auto& c) { if (c != '#') c = 'O'; };
                    updateIfNotRock(nextMap[y][x + 1]);
                    updateIfNotRock(nextMap[y][x - 1]);
                    updateIfNotRock(nextMap[y + 1][x]);
                    updateIfNotRock(nextMap[y - 1][x]);
                }
            }
        }
        map.swap(nextMap);
    }

    // for (auto& r: map)std::cout << r << '\n';
    // std::cout << '\n';

    auto const cnt = std::accumulate(map.begin(), map.end(), std::make_signed_t<U>{}, [](auto acc, auto& str) {
        return acc + r4s::count(str, 'O');
    });

    std::cout << "Nr of plots to reach is " << cnt << '\n';

    return EXIT_SUCCESS;
}
