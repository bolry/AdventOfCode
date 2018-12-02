#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <map>

typedef std::map<char, int> Map;
typedef Map::value_type ValType;

struct find_value{
  int value_to_find;
  explicit find_value(int val): value_to_find(val){}
  bool operator()(ValType const & a ) const {
      return a.second == value_to_find;
  }
};

int main(int argc, char *argv[])
try {
    std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
    if (argc < 2) throw std::runtime_error("Need input data filename\n");
    std::ifstream id_file(argv[1]);
    if (!id_file) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
    std::istream_iterator<std::string> id_reader(id_file);
    std::istream_iterator<std::string> id_reader_EOF;
    int two_count = 0;
    int three_count = 0;
    std::map<char,int> counter;
    for(;id_reader != id_reader_EOF; ++id_reader){
        counter.clear();
        for( auto const& id : *id_reader){
            ++counter[id];
        }
        auto findee = std::find_if(counter.begin(), counter.end(), find_value(2));
        if(findee != counter.end()){
            two_count++;
        }
        findee = std::find_if(counter.begin(), counter.end(), find_value(3));
        if(findee != counter.end()){
            three_count++;
        }
    }
    int const checksum = two_count * three_count;
    std::cout << checksum << '\n' << std::flush;
    return EXIT_SUCCESS;
}
catch (std::bad_alloc const &) {
    std::fputs("Sorry, out-of-memory\n", stderr);
    std::fflush(stderr);
    return EXIT_FAILURE;
}
catch (std::exception const &x) {
    std::cerr << x.what() << '\n' << std::flush;
    return EXIT_FAILURE;
}
#if 0
catch (...) {
    std::cerr << "Unexpected unhandled error\n" << std::flush;
    return EXIT_FAILURE;
}
#endif  // 0
