#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <new>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

int main(int argc, char *argv[])
try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("Need input data filename\n");
  std::ifstream polymer_file(argv[1]);
  if (!polymer_file) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
  std::string polymer;
  polymer_file >> polymer;
  //std::cout << '`' << polymer << "'\n";
  while (true) {
    auto
        reaction = std::adjacent_find(polymer.begin(), polymer.end(), [](unsigned char const a, unsigned char const b) {
      return a != b && std::toupper(a) == std::toupper(b);
    });
    if (reaction == polymer.end()) break;
    polymer.erase(reaction, reaction + 2);
    //std::cout << '`' << polymer << "'\n";
  }
  std::cout << "Polymer length is " << polymer.size() << '\n';
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
