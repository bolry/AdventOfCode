#include <algorithm>
#include <cassert>
#include <fstream>
#include <limits>
#include <numeric>
#include <vector>

#include <fmt/format.h>

using fmt::print;

int calc(int pos, std::vector<int> const &v) {
    return std::accumulate(v.begin(), v.end(), 0, [pos](int a, int b) { return a + std::abs(pos - b); });
}

int main() {
    std::ifstream ifs{"../input.txt"};
    assert(ifs);
    std::vector<int> v;
    char c;
    for (int i; ifs >> i; ifs >> c) {
        v.push_back(i);
    }
    auto mm = std::minmax_element(v.begin(), v.end());
    int best = std::numeric_limits<int>::max();
    for (int i = *mm.first; i <= *mm.second; ++i) {
        int cal = calc(i, v);
        print("Cost for pos {} is {}\n", i, cal);
        best = std::min(best, cal);
    }
    print("Best result {}\n", best);
}
