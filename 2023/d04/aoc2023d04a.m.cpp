// https://adventofcode.com/2023/day/4

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {
    struct Card {
        int id{};
        std::vector<int> winNums;
        std::vector<int> nums;

        friend std::istream& operator>>(std::istream& ins, Card& card) {
            if (std::string row; std::getline(ins, row)) {
                std::istringstream iss{std::move(row)};
                auto& _ = row; // reuse for ignoring stuff, thus new name
                iss >> _ >> card.id >> _;
                card.winNums.assign(std::istream_iterator<int>{iss}, {});
                std::ranges::sort(card.winNums);
                iss.clear(); // we found the '|'
                iss.ignore(); // skip it
                card.nums.assign(std::istream_iterator<int>{iss}, {});
                std::ranges::sort(card.nums);
                // std::cout << 'C' << card.id << ": WIN ";
                // for (auto &e: card.winNums) std::cout << e << ' ';
                // std::cout << " NUM ";
                // for (auto &e: card.nums) std::cout << e << ' ';
                // std::cout << '\n';
            }
            return ins;
        }
    };

    constexpr int powInt(int base, int exponent) noexcept {
        int result{1};
        while (exponent > 0) {
            auto dv = std::div(exponent, 2);
            if (dv.rem == 1) result *= base;
            base *= base;
            exponent = dv.quot;
        }
        return result;
    }


    int getScore(Card const& card) {
        std::vector<int> score;
        std::ranges::set_intersection(card.winNums, card.nums, std::back_inserter(score));
        // std::cout << "COMMON ";
        // for (auto &e: score) std::cout << e << ' ';
        int const res{score.empty() ? 0 : powInt(2, static_cast<int>(score.size() - 1))};
        // std::cout << " SCORE " << res << '\n';
        return res;
    }
}

int main([[maybe_unused]] int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);

    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    auto const sum = std::accumulate(std::istream_iterator<Card>{ifs}, {}, 0, [](int acc, Card const& card) {
        return acc + getScore(card);
    });

    std::cout << "Sum is " << sum << std::endl;
    return EXIT_SUCCESS;
}
