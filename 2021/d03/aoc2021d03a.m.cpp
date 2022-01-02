#include <array>
#include <bitset>
#include <cassert>
#include <fstream>

#include <fmt/format.h>

int main() {
    std::ifstream ifs{"../input.txt"};
    assert(ifs);
    std::bitset<12> bitset;
    std::array<int, 12> setBits{};
    std::array<int, 12> offBits{};
    while (ifs >> bitset) {
        for (int i{}; i != 12; ++i) {
            if (bitset.test(i)) ++setBits[i];
            else ++offBits[i];
        }
    }
    ifs.close();
    std::bitset<12> gammaRate{};
    std::bitset<12> epsilonRate{};
    for (int i{}; i != 12; ++i) {
        gammaRate.set(i, offBits[i] < setBits[i]);
        epsilonRate.set(i, setBits[i] < offBits[i]);
        assert(setBits[i] != offBits[i]);
    }

    fmt::print("Gamma is {} epsione is {}\n", gammaRate.to_ulong(), epsilonRate.to_ulong());
    fmt::print("anser {}\n", gammaRate.to_ulong() * epsilonRate.to_ulong());
}
