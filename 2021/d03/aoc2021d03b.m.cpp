#include <algorithm>
#include <bitset>
#include <cassert>
#include <fstream>
#include <vector>

#include <fmt/format.h>

using Bitset = std::bitset<12>;

Bitset calc(std::vector<Bitset> &input, bool prefer, int pos = Bitset().size() - 1) {
    assert(!input.empty());
    if (input.size() == 1) return input.front();
    assert(0 <= pos);
    int setBits{};
    int offBits{};
    for (auto const &bitset: input)
        if (bitset.test(pos)) ++setBits;
        else ++offBits;
    bool keepFlag{setBits < offBits == !prefer};

    std::erase_if(input, [pos, keepFlag](Bitset const &bitset) { return bitset.test(pos) != keepFlag; });
    return calc(input, prefer, pos - 1);
}

int main() {
    std::ifstream ifs{"../input.txt"};
    assert(ifs);
    std::vector<Bitset> oxygenInput(std::istream_iterator<Bitset>{ifs}, {});
    ifs.close();
    auto co2Input{oxygenInput};

    auto oxygen{calc(oxygenInput, true)};
    auto co2{calc(co2Input, false)};

    fmt::print("oxygen is {} co2 is {}\n", oxygen.to_ulong(), co2.to_ulong());
    fmt::print("answer {}\n", oxygen.to_ulong() * co2.to_ulong());
}
