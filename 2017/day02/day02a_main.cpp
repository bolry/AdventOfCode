#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

int main() {
    auto checksum = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream str(line);
        auto result = std::minmax_element(std::istream_iterator<int>(str), std::istream_iterator<int>());
        checksum += *result.second - *result.first;
    }
    std::cout << "The checksum is " << checksum << '\n';
}