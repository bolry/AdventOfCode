#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

namespace {
    typedef std::vector<int> IntVec;
    typedef IntVec::const_iterator VecIter;
    typedef std::istream_iterator<int> StreamIter;
}

int main(int argc, char *argv[])
try {
    std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
    if (argc < 2) throw std::runtime_error("Need input data\n");
    std::ifstream freq_change_file(argv[1]);
    if (!freq_change_file) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
    IntVec frequency_change_list;
    std::copy(StreamIter(freq_change_file), StreamIter(),
              std::back_insert_iterator<IntVec>(frequency_change_list));
    std::set<int> seen_frequencies;
    int current_frequency = 0;
    VecIter const last = frequency_change_list.end();
    while (true) {
        VecIter first = frequency_change_list.begin();
        for (; first != last; ++first) {
            current_frequency += *first;
            bool const isReusedFrequency = !seen_frequencies.insert(current_frequency).second;
            if (isReusedFrequency) {
                int const &duplicate_frequency = current_frequency;
                std::cout << duplicate_frequency << '\n' << std::flush;
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
