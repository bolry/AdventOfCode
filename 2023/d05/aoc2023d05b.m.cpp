// https://adventofcode.com/2023/day/5#part2

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <span>
#include <string>
#include <vector>

namespace {
    constexpr auto until = std::numeric_limits<std::streamsize>::max();
    namespace r4s = std::ranges;
    using U = std::uintmax_t;
    template<typename T>
    using InIter = std::istream_iterator<T>;

    struct SeedRng {
        U start;
        U len;

        friend std::istream& operator>>(std::istream& in, SeedRng& seedRng) {
            in >> seedRng.start >> seedRng.len;
            return in;
        }
    };

    struct Subrange {
        U dest;
        U source;
        U len;

        friend bool operator<(Subrange const& a, Subrange const& b) noexcept {
            return a.source < b.source;
        }

        friend std::istream& operator>>(std::istream& in, Subrange& rng) {
            in >> rng.dest >> rng.source >> rng.len;
            return in;
        }
    };


    struct Map {
        std::string name;
        std::vector<Subrange> ranges;

        friend std::istream& operator>>(std::istream& in, Map& map) {
            if (std::string ign; in >> map.name >> ign) {
                assert(ign=="map:");
                map.ranges.assign(InIter<Subrange>{in}, {});
                assert(!in.bad());
                // can't check eof
                assert(in.fail());
                in.clear();
                std::sort(map.ranges.begin(), map.ranges.end());
            }
            return in;
        }
    };

    U lookup(std::span<Subrange const> const ranges, U const s) {
        Subrange matcher{};
        matcher.source = s;
        auto iter = std::lower_bound(ranges.begin(), ranges.end(), matcher);
        if (iter != ranges.end()) {
            if (iter->source == s) return s - (iter->source - iter->dest);
            else if (iter != ranges.begin()) {
                if (std::advance(iter, -1); iter->source <= s && s < iter->source + iter->len)
                    return s - (iter->source - iter->dest);
            }
        } else if (auto const& [dest, source, len] = ranges.back(); source <= s && s < source + len) {
            return s - (source - dest);
        }
        return s;
    }

    U locationFromSeed(std::span<Map const> const maps, U s) {
        for (auto const& map: maps) {
            s = lookup(map.ranges, s);
        }
        return s;
    }
}

int main([[maybe_unused]] int argc, char* argv[]) {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    ifs.ignore(until, ' '); // Skip "seeds:"

    std::vector<SeedRng> seedRanges(InIter<SeedRng>{ifs}, {});

    assert(!ifs.bad());
    assert(!ifs.eof());
    assert(ifs.fail());

    ifs.clear();

    std::vector<Map> maps(InIter<Map>{ifs}, {});

    assert(!ifs.bad());
    assert(ifs.eof());
    assert(ifs.fail());

    U bestLocation{std::numeric_limits<U>::max()};

    for (auto const& seedRng: seedRanges) {
        for (U i{seedRng.start}, e{i + seedRng.len}; i != e; ++i) {
            bestLocation = std::min(bestLocation, locationFromSeed(maps, i));
        }
    }

    std::cout << "Lowest location is " << bestLocation << '\n';

    return EXIT_SUCCESS;
}
