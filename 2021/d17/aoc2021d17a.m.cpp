
using namespace std::literals;
using fmt::print;

constexpr auto indata{"target area: x=209..238, y=-86..-59"sv};

bool inRange(int x, int low, int high) noexcept {
    return !(x < low || high < x);
}

bool inRange(int x, int y) noexcept {
    return inRange(x, 209, 238) && inRange(y, -86, -59);
}

int main() {
    int xPos{}, yPos{};
    int dx{20}, dy{85};
    int bestY{std::numeric_limits<int>::min()};
    while (!inRange(xPos, yPos)) {
        // update
        xPos += dx;
        yPos += dy;
        if (auto res{dx <=> 0};res < 0) ++dx;
        else if (res > 0) --dx;
        --dy;
        print("({}, {})\n", xPos, yPos);
        bestY = (std::max)(bestY, yPos);
        if (xPos > 238 || yPos < -86) return EXIT_FAILURE;
    }
    print("best Y is {}\n", bestY);
}
