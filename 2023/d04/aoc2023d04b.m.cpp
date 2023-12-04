// https://adventofcode.com/2023/day/4#part2

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {
    namespace r4s = std::ranges;

    struct Card {
        int id{};
        std::vector<int> winNums;
        std::vector<int> nums;

        friend std::istream& operator>>(std::istream& ins, Card& card) {
            if (std::string row; std::getline(ins, row)) {
                card = {};
                std::istringstream iss{std::move(row)};
                auto& _ = row; // use for junk
                iss >> _ >> card.id >> _; // "Card NN:"
                card.winNums.assign(std::istream_iterator<int>{iss}, {});
                assert(iss.fail());
                iss.clear(); // we found the '|'
                iss.ignore(); // so skip it
                r4s::sort(card.winNums); // needed for set operations later
                card.nums.assign(std::istream_iterator<int>{iss}, {});
                assert(iss.eof());
                r4s::sort(card.nums); // needed for set operations later
            }
            return ins;
        }
    };

    // Needed for transparent comparison
    constexpr bool operator<(Card const& card1, int const num2) noexcept { return card1.id < num2; }
    constexpr bool operator<(int const num1, Card const& card2) noexcept { return num1 < card2.id; }
    constexpr bool operator<(Card const& card1, Card const& card2) noexcept { return card1.id < card2.id; }

    int getScore(Card const& card) {
        std::vector<int> score;
        r4s::set_intersection(card.winNums, card.nums, std::back_inserter(score));
        return static_cast<int>(score.size());
    }
}

int main([[maybe_unused]] int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);

    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    // Transparent comparison
    std::map<Card, int, std::less<>> cards;

    for (std::istream_iterator<Card> b{ifs}, e{}; b != e; ++b) ++cards[*b];

    // play each card and duplicate the winning counts of the next cards
    for (auto const& [card, cnt]: cards)
        for (int id{card.id + 1}, maxId{card.id + getScore(card)}; id <= maxId; ++id)
            cards.find(id)->second += cnt;

    auto const count = std::accumulate(cards.begin(), cards.end(), 0, [](int acc, auto const& valPair) {
        return acc + valPair.second;
    });

    std::cout << "Count of cards is " << count << std::endl;
    return EXIT_SUCCESS;
}
