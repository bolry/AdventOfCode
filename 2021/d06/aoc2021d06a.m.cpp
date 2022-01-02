#include <cassert>
#include <fstream>
#include <span>
#include <vector>

#include <fmt/format.h>

void evolveOneDay(std::vector<int> &v) {
    int cntNew{};
    for (auto &i: v)
        if (i) --i;
        else {
            ++cntNew;
            i = 6;
        };
    v.insert(v.end(), cntNew, 8);
}

void p(std::span<int const> s) {
    for (auto v: s) fmt::print("{},", v);
    fmt::print("\n");
}

int main() {
    std::ifstream ifs{"../input.txt"};
    assert(ifs);
    std::vector<int> v;
    char c;
    for (int i; ifs >> i; ifs >> c) v.push_back(i);
    fmt::print("Initial state: ");
    p(v);
    for (int day{}; day < 80;) {
        ++day;
        evolveOneDay(v);
        fmt::print("After {} days (len {}): ", day, v.size());
        p(v);
    }
    fmt::print("After 80 days length {}", v.size());
}
