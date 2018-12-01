#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[])
try {
    std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
    if (argc < 2) throw std::runtime_error("Need input data\n");
    std::ifstream in(argv[1]);
    if (!in) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
    std::vector<int> frequencies;
    int value;
    while (in >> value)
        frequencies.push_back(value);
    std::unordered_map<int, int> seen;
    int init = 0;
    while(true) {
        for (auto first = begin(frequencies), last = end(frequencies); first != last; ++first) {
            init += *first;
            if (seen[init]++) {
                std::cout << init << '\n' << std::flush;
                return EXIT_SUCCESS;
            }
        }
    }
}
catch (std::bad_alloc const &) {
    std::fputs("Sorry, out-of-memory\n", stderr);
}
catch (std::exception const &e) {
    std::cerr << "Got exception: " << e.what() << '\n';
}
catch (...) {
    std::cerr << "Unexpected unhandled error\n";
}