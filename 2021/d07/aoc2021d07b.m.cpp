#include <algorithm>
#include <cassert>
#include <fstream>
#include <limits>
#include <numeric>
#include <vector>

#include <fmt/format.h>

using fmt::print;

std::vector k{0};

int getCost(int dist) {
    if (dist < k.size()) return k[dist];
    k.reserve(dist+1);
    for (int i = k.size(); i <= dist; ++i) {
        k.push_back(k[i - 1] + i);
    }
    return k[dist];
}

int calc(int pos, std::vector<int> const &v) {
    return std::accumulate(v.begin(), v.end(), 0, [pos](int a, int b) { return a + getCost(std::abs(pos - b)); });
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
        print("Cost for {} is {}\n", i, cal);
        best = std::min(best, cal);
    }

    print("\nK size is {}\n", k.size());
    print("\nBest result {}\n", best);
}
