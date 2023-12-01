// https://adventofcode.com/2023/day/1

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>  // where some algorithms go to hide
#include <string>
#include <string_view>

namespace {
    constexpr int calibrationValue(std::string_view const line) noexcept {
        constexpr std::string_view kDigits{"1234567890"};

        auto const firstPos = line.find_first_of(kDigits);

        [[maybe_unused]] constexpr auto npos = std::string_view::npos;
        assert(firstPos != npos);

        auto const lastPos = line.find_last_of(kDigits);
        assert(lastPos != npos);

        int const firstDigit{line[firstPos] - '0'};
        int const lastDigit{line[lastPos] - '0'};

        return firstDigit * 10 + lastDigit;
    }
}

int main([[maybe_unused]] int const argc, char* const argv[]) {
    std::ios_base::sync_with_stdio(false);

    assert(argc==2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    auto const sum = std::accumulate(std::istream_iterator<std::string>{ifs}, {}, 0,
                                     [](int const acc, std::string_view const line) {
                                         return acc + calibrationValue(line);
                                     });

    std::cout << "The total sum of all calibration values is " << sum << '.' << std::endl;

    return EXIT_SUCCESS;
}
