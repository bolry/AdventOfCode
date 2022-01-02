#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <unordered_map>

#include <fmt/format.h>

struct Line {
    int x1, y1;
    int x2, y2;

    friend std::istream &operator>>(std::istream &in, Line &seg) {
        std::string arrow;
        char c;
        do {
            // "9,4 -> 3,4"
            in >> seg.x1 >> c >> seg.y1 >> arrow >> seg.x2 >> c >> seg.y2;
        } while (in && (seg.x1 != seg.x2) && (seg.y1 != seg.y2));
        return in;
    }
};

int main() {
    std::ifstream ifs{"../input.txt"};
    std::unordered_map<int, std::unordered_map<int, int>> dia;
    Line seg;
    while (ifs >> seg) {
        if (seg.x1 == seg.x2) {
            int x{seg.x1};
            int mi{std::min(seg.y1, seg.y2)};
            int ma{std::max(seg.y1, seg.y2)};
            auto &theX{dia[x]};
            for (int y{mi}; y <= ma; ++y) {
                theX[y]++;
            }
        } else if (seg.y1 == seg.y2) {
            int y{seg.y1};
            int mi{std::min(seg.x1, seg.x2)};
            int ma{std::max(seg.x1, seg.x2)};
            for (int x{mi}; x <= ma; ++x) {
                dia[x][y]++;
            }
        } else
            assert(false);
    }
    ifs.close();
    int cnt{};
    for (auto const &[x, col]: dia)
        for (auto const&[y, val]: col)
            if (val >= 2) ++cnt;

    fmt::print("{}\n", cnt);
}
