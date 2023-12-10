// https://adventofcode.com/2023/day/5

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

    struct Subrange {
        U dest;
        U source;
        U len;

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
            }
            return in;
        }
    };

    U lookup( std::span<Subrange const> ranges, U s) {
        for(auto const& subRng: ranges) {
            if(subRng.source <= s  &&  s < (subRng.source+subRng.len)) {
                return s - (subRng.source - subRng.dest);
            }
        }
        return s;
    }

    U locationFromSeed(std::span<Map const> maps, U s) {
        for(auto const& map : maps) {
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
    std::vector<U> const seeds(InIter<U>{ifs}, {});

    assert(!ifs.bad());
    assert(!ifs.eof());
    assert(ifs.fail());
    ifs.clear();

    std::vector<Map> const maps(InIter<Map>{ifs}, {});

    assert(!ifs.bad());
    assert(ifs.eof());
    assert(ifs.fail());

    std::vector<U> locations;
    locations.resize(seeds.size());
    r4s::transform(seeds, locations.begin(), [&maps](auto const& seed) {
        return locationFromSeed(maps, seed);
    });

    std::cout << "Lowest location is " << *r4s::min_element(locations) << '\n';

    return EXIT_SUCCESS;
}
