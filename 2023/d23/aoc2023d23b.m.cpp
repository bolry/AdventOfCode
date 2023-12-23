// https://adventofcode.com/2023/day/23#part2

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <span>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
    using InIter = std::istream_iterator<std::string>;
    using I = int;
    using U = std::make_unsigned_t<I>;

    // NOLINTBEGIN(*-no-recursion)
    void findLongestPath(std::span<std::string const> const& maze, U const x, U const y,
                         std::vector<std::string>& visited, I len, I& maxLen) {
        // NOLINTEND(*-no-recursion)
        if (std::cmp_equal(x, 0) || std::cmp_equal(y, 0)) return;

        auto const mazeYsz = maze.size();

        if (std::cmp_greater_equal(y, mazeYsz)) return;

        auto const& row = maze[y];

        if (std::cmp_greater_equal(x, row.size()) || row[x] == '#') return;

        auto& haveVisited = visited[y][x];

        if (haveVisited) return;

        haveVisited = {true};

        ++len;

        if (y == mazeYsz - 1) maxLen = std::max(maxLen, len);

        // Explore neighbors
        findLongestPath(maze, x + 1, y, visited, len, maxLen);
        findLongestPath(maze, x - 1, y, visited, len, maxLen);
        findLongestPath(maze, x, y + 1, visited, len, maxLen);
        findLongestPath(maze, x, y - 1, visited, len, maxLen);

        // Backtrack
        haveVisited = {false};
        --len;
    }
} // anonymous namespace

int main([[maybe_unused]] int const argc, char* argv[]) {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    std::vector<std::string> const map(InIter{ifs}, {});
    assert(!map.empty());
    std::vector<std::string> visits(map.size(), std::string(map.front().size(), {}));

    I maxLen{};

    assert(map.front().at(1) == '.'); // entrance
    findLongestPath(map, 1, 1, visits, 0, maxLen);

    std::cout << "The hike contains " << maxLen << " steps\n";

    return EXIT_SUCCESS;
}
