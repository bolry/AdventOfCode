// https://adventofcode.com/2023/day/9

#include <algorithm>
#include <cassert>
#include <cstdint>
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
    namespace r4s = std::ranges;
    using S = std::intmax_t;

    struct History {
        std::vector<S> sample;

        friend std::istream& operator>>(std::istream& in, History& history) {
            if (std::string line; std::getline(in, line)) {
                std::istringstream iss{std::move(line)};
                history.sample.assign(std::istream_iterator<S>{iss}, {});
            }
            return in;
        }
    };

    auto calcDiff = [](std::vector<S> const& in, std::vector<S>& out) {
        out.resize(in.size());
        (void) std::adjacent_difference(in.begin(), in.end(), out.begin());
    };

    S nextValue(History hist) {
        auto& diffs(hist.sample);
        std::vector<S> lasts;
        lasts.push_back(diffs.back());
        std::vector<S> tmp;
        do {
            calcDiff(diffs, tmp);
            lasts.push_back(tmp.back());
            diffs.assign(std::next(tmp.begin()), tmp.end());
        } while (r4s::any_of(diffs, [](auto v) { return v != 0; }));
        return std::accumulate(lasts.begin(), lasts.end(), S{});
    }
}

int main([[maybe_unused]] int argc, char* argv[]) {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    auto const sum = std::accumulate(std::istream_iterator<History>{ifs}, {}, S{}, [](S acc, auto const& hist) {
        return acc + nextValue(hist);
    });

    std::cout << "The sum of the extrapolated values is " << sum << '\n';

    return EXIT_SUCCESS;
}
