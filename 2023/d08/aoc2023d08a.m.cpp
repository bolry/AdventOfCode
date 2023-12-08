// https://adventofcode.com/2023/day/8

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

namespace {
    struct Val {
        std::string left;
        std::string right;
    };
}

int main([[maybe_unused]] int argc, char* argv[]) {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    std::string lrInstruct;
    std::getline(ifs, lrInstruct);

    std::unordered_map<std::string, Val> nodes;
    std::string key;
    Val val;
    char ign; // ignore
    while (ifs >> key >> ign >> val.left >> val.right) {
        assert(ign == '=');
        val.left.pop_back();
        val.left.erase(val.left.begin());
        val.right.pop_back();
        nodes[key] = val;
    }
    ifs.close();

    // std::cout << "Instructions " << lrInstruct << '\n';
    // for(auto const& [k, v]:network) {
    //     std::cout << k << ' ' << v.left << ' ' << v.right << '\n';
    // }

    std::uintmax_t stepCnt{};
    std::string_view next{lrInstruct};
    constexpr std::string_view end{"ZZZ"};
    for (std::string elem{"AAA"}; elem != end;) {
        if (next.empty()) next = lrInstruct;
        ++stepCnt;
       auto const& hmm= nodes.at(elem);
        if(next.front() == 'L') elem = hmm.left; else elem=hmm.right;
        next.remove_prefix(1);
    }

    std::cout << "Steps taken " << stepCnt << '\n';

    return EXIT_SUCCESS;
}
