// https://adventofcode.com/2023/day/7#part2

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
    using U = unsigned;
    namespace r4s = std::ranges;

    enum Type: std::uint_least8_t {
        Highcard,
        Onepair,
        Twopair,
        Threeofakind,
        Fullhouse,
        Fourofakind,
        Fiveofakind,
    };

    Type getType(std::string_view hand) {
        std::unordered_map<char, int> freq;
        U jCnt{};
        for (char c: hand)
            if (c != 'J') ++freq[c];
            else ++jCnt;

        switch (jCnt) {
            case 1: if (auto sz = freq.size(); sz == 1) return Fiveofakind;
                else if (sz == 2) {
                    auto iter = freq.begin();
                    if (auto cnt = freq.at(iter->first); cnt == 1 || cnt == 3) return Fourofakind;
                    else return Fullhouse;
                }
                else if (sz == 3) return Threeofakind;
                else return Onepair;
            case 2: if (auto sz = freq.size(); sz == 1) return Fiveofakind;
                else if (sz == 2) return Fourofakind;
                else return Threeofakind;
            case 3: if (freq.size() == 1) return Fiveofakind;
                else return Fourofakind;
            case 4: return Fiveofakind;
            case 5: return Fiveofakind;
        }

        switch (freq.size()) {
            case 1: return Fiveofakind;
            case 2: if (auto cnt = freq.at(hand.front()); cnt == 1 || cnt == 4) return Fourofakind;
                else return Fullhouse;
            case 3: if (r4s::any_of(freq, [](auto const& pair) { return pair.second == 3; })) return Threeofakind;
                else return Twopair;
            case 4: return Onepair;
            case 5: return Highcard;
        }
        std::unreachable();
    }

    bool lessHighcard(std::string_view lHand, std::string_view rHand) noexcept {
        // A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2
        constexpr auto value = []() {
            U res[256]{};
            res['2'] = 1;
            res['3'] = 2;
            res['4'] = 3;
            res['5'] = 4;
            res['6'] = 5;
            res['7'] = 6;
            res['8'] = 7;
            res['9'] = 8;
            res['T'] = 9;
            res['J'] = 0;
            res['Q'] = 11;
            res['K'] = 12;
            res['A'] = 13;
            return std::to_array(res);
        }();
        for (auto idx: {0u, 1u, 2u, 3u}) {
            auto left = value[static_cast<unsigned char>(lHand[idx])];
            auto right = value[static_cast<unsigned char>(rHand[idx])];
            if (left < right) return true;
            else if (right < left) return false;
        }
        return value[static_cast<unsigned char>(lHand[4])] < value[static_cast<unsigned char>(rHand[4])];
    }

    struct CamelCards {
        std::string hand;
        U bet{};

        friend std::ostream& operator<<(std::ostream& os, CamelCards const& obj) {
            return os
                   << "hand: " << obj.hand
                   << " bet: " << obj.bet;
        }

        friend bool operator<(CamelCards const& lhs, CamelCards const& rhs) {
            auto lType = getType(lhs.hand);
            auto rType = getType(rhs.hand);
            if (lType < rType) return true;
            if (rType < lType) return false;
            return lessHighcard(lhs.hand, rhs.hand);
        }

        friend std::istream& operator>>(std::istream& in, CamelCards& camelCard) {
            in >> camelCard.hand >> camelCard.bet;
            if (in)
                assert(camelCard.hand.size()==5);
            return in;
        }
    };
}

int main([[maybe_unused]] int argc, char* argv[]) {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    std::vector<CamelCards> hands(std::istream_iterator<CamelCards>{ifs}, {});
    std::sort(hands.begin(), hands.end());

    //  for(auto const& x: hands) std::cout << x <<'\n';

    std::uintmax_t prod{};
    U idx{};
    for (auto const& x: hands) prod += x.bet * ++idx;

    std::cout << "Result " << prod << '\n';

    return EXIT_SUCCESS;
}
