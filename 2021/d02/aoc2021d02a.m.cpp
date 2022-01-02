#include <cassert>
#include <fstream>
#include <string>
#include <string_view>

#include <fmt/format.h>

using namespace std::literals;

int main() {
    std::ifstream ifs{"../input.txt"};
    int depth{};
    int horpos{};
    std::string command;
    int value;

    while (ifs >> command >> value)
        if (command == "forward"sv) horpos += value;
        else if (command == "down"sv) depth += value;
        else if (command == "up"sv) depth -= value;
        else assert(false);

    fmt::print("depth {} hor.pos {} multiply is {}\n", depth, horpos, depth * horpos);
}
