#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <numeric>

#include <fmt/format.h>

void evolveOneDay(std::array<std::uintmax_t, 9> &v) {
    std::rotate(v.begin(), std::next(v.begin()), v.end());
    v[6] += v.back();
}

int main() {
    std::ifstream ifs{"../input.txt"};
    assert(ifs);
    std::array<std::uintmax_t, 9> v{};
    char c;
    for (int i; ifs >> i; ifs >> c) ++v[i];

    fmt::print("Initial state: len {}\n", std::accumulate(v.begin(), v.end(), std::uintmax_t{}));
    for (int day{}; day < 256;) {
        ++day;
        evolveOneDay(v);
        fmt::print("After {} days len {}\n", day, std::accumulate(v.begin(), v.end(), std::uintmax_t{}));
    }
}
