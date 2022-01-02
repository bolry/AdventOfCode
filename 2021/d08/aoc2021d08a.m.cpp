#include <fstream>
#include <cassert>
#include <string>

#include <fmt/core.h>

int main() {
    std::ifstream ifs{"../input.txt"};
    assert(ifs && "can't find file to open");
    std::string s;
    int cnt{};
    while (ifs >> s) {
        for (int i{}; i < 10; ++i) ifs >> s;
        assert(s == "|");
        for (int i{}; i < 4; ++i) {
            assert(ifs >> s);
            switch (int sz = s.size(); sz) {
                case 2:
                case 3:
                case 7:
                case 4:
                    ++cnt;
            }
        }
    }
    fmt::print("{}\n", cnt);
}
