#include <cassert>
#include <fstream>
#include <string>
#include <string_view>

#include <fmt/format.h>

using namespace std::string_view_literals;

int main() {
    std::ifstream ifs{"../input.txt"};
    int depth{};
    int horpos{};
    int aim{};
    std::string command;
    int value;
    while (ifs >> command >> value)
        if (command == "forward"sv) horpos += value, depth += value * aim;
        else if (command == "down"sv) aim += value;
        else if (command == "up"sv) aim -= value;
        else assert(false);

    fmt::print("depth {} hor.pos {} multiply is {}\n", depth, horpos, depth * horpos);
}
