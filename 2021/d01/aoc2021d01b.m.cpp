#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <fmt/ostream.h>

int main() {
    fmt::print("Welcome to Advent of Code 2021 day 01 part 2\n");
    std::ifstream ifs{"../input.txt"};
    assert(ifs);
    std::istream_iterator<int> b{ifs}, e{};
    std::vector<int> windows;
    std::array<int, 3> win;
    win[0] = *b;
    ++b;
    win[1] = *b;
    ++b;
    while (b != e) {
        win[2] = *b;
        ++b;
        fmt::print("last {}\n", win[2]);
        windows.push_back(std::accumulate(win.begin(), win.end(), 0));
        std::copy(std::next(win.begin()), win.end(), win.begin());
    }
    int incCount{};
    int lastValue{std::numeric_limits<int>::max()};
    for (int v: windows) {
        incCount += v > lastValue;
        lastValue = v;
    }
    fmt::print("Number inc windows is {}\n", incCount);
    return EXIT_SUCCESS;
}
