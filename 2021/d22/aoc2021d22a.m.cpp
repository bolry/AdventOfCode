
#include <istream>

constexpr int dimMin{-50};
constexpr int dimMax{50};
constexpr int dimSz{dimMax - dimMin + 1};

using Dim = std::bitset<dimSz>;

using Reactor = std::array<std::array<Dim, dimSz>, dimSz>;

using fmt::print;

struct RebootStep {
    bool isOn;
    int xMin, xMax;
    int yMin, yMax;
    int zMin, zMax;

    friend std::istream &operator>>(std::istream &in, RebootStep &step) {
        std::string onOff;
        char xyz, eq, comma, p;
        // on x=10..12,y=10..12,z=10..12
        in >> onOff >> xyz >> eq >> step.xMin >> p >> p >> step.xMax
           >> comma >> xyz >> eq >> step.yMin >> p >> p >> step.yMax
           >> comma >> xyz >> eq >> step.zMin >> p >> p >> step.zMax;
        step.isOn = onOff == "on";
        return in;
    }
};

int main(int, char *argv[]) {
    assert(argv[1] && "missing filename argument");
    std::ifstream ifs{argv[1]};
    assert(ifs && "unable to open file");
    Reactor reactor;
    RebootStep rs;
    while (ifs >> rs) print("ok\n");
}
