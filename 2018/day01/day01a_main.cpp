#include <cstdio>
#include <numeric>
#include <iterator>
#include <iostream>
#include <vector>
#include <fstream>

int main(int argc, char *argv[])
try {
    std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
    if (argc < 2) throw std::runtime_error("Need input data\n");
    std::ifstream in(argv[1]);
    if (!in) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
    std::vector<int> freq;
    int value;
    while (in >> value)
        freq.push_back(value);
    std::cout << std::accumulate(begin(freq), end(freq), 0) << '\n' << std::flush;
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