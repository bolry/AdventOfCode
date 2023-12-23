// https://adventofcode.com/2023/day/23

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
    void findIcyPath(std::span<std::string const> const maze, U x, U y,
                     std::span<std::vector<bool>> visited, I len, I& maxLen) {
        // NOLINTEND(*-no-recursion)

        if (std::cmp_equal(x, 0) || std::cmp_equal(y, 0) || std::cmp_greater_equal(y, maze.size())) return;

        auto const& row = maze.at(y);

        if (std::cmp_greater_equal(x, row.size())) return;

        auto const tile = row.at(x);

        // check for wall
        if (tile == '#') return;

        auto hasBeenVisited = visited[y][x];

        if (hasBeenVisited) return;

        hasBeenVisited = {true};
        ++len;

        maxLen = std::max(maxLen, len);

        // Explore neighbors
        switch (tile) {
                [[likely]] case '.':
                findIcyPath(maze, x + 1, y, visited, len, maxLen);
                findIcyPath(maze, x - 1, y, visited, len, maxLen);
                findIcyPath(maze, x, y + 1, visited, len, maxLen);
                findIcyPath(maze, x, y - 1, visited, len, maxLen);
                break;
            case '^':
                findIcyPath(maze, x, y - 1, visited, len, maxLen);
                break;
            case '>':
                findIcyPath(maze, x + 1, y, visited, len, maxLen);
                break;
            case 'v':
                findIcyPath(maze, x, y + 1, visited, len, maxLen);
                break;
            case '<':
                findIcyPath(maze, x - 1, y, visited, len, maxLen);
                break;
            default: std::unreachable();
        }

        // Backtrack
        hasBeenVisited = {false};
        --len;
    }
} // anonymous namespace

int main([[maybe_unused]] int argc, char* argv[]) {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    std::vector<std::string> const map(InIter{ifs}, {});
    std::vector<std::vector<bool>> visits(map.size(), std::vector<bool>(map.front().size()));

    I maxLen{};
    findIcyPath(map, 1, 1, visits, 0, maxLen);

    std::cout << "The hike contains " << maxLen << " steps\n";

    return EXIT_SUCCESS;
}
