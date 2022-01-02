#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <vector>

#include <fmt/core.h>

namespace rg = std::ranges;

int main() {
    fmt::print("Welcome to Advent of Code 2021 day 01 part 1\n");
    std::ifstream ifs{"../input.txt"};
    std::vector<int> const v(std::istream_iterator<int>{ifs}, {});
    ifs.close();
    int incCount{};
    for (auto b = rg::adjacent_find(v, std::less<int>{});
         b != rg::end(v);
         b = rg::adjacent_find(b, rg::end(v), std::less<int>{})) {
        ++incCount;
        ++b;
    }


    fmt::print("Number increments is {}\n", incCount);
    return EXIT_SUCCESS;
}
