#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <new>
#include <string>

namespace {

int test_polymer(unsigned char const unit, std::string polymer) {
  int const U = std::toupper(unit);
  auto reaction = polymer.begin();
  auto const new_end = std::remove_if(reaction, polymer.end(), [U](unsigned char a) {
    return U == std::toupper(a);
  });
  polymer.erase(new_end, polymer.end());
  while (true) {
    reaction = std::adjacent_find(reaction, polymer.end(), [](unsigned char const a, unsigned char const b) {
      return a != b && std::toupper(a) == std::toupper(b);
    });
    if (reaction == polymer.end()) break;
    reaction = polymer.erase(reaction, reaction + 2);
    if (reaction != polymer.begin()) --reaction;
    //std::cout << '`' << polymer << "'\n";
  }
  return polymer.size();
}

}  // close anonymous namespace

int main(int argc, char *argv[])
try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("Need input data filename\n");
  std::ifstream polymer_file(argv[1]);
  if (!polymer_file) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
  std::string polymer;
  polymer_file >> polymer;
  //std::cout << '`' << polymer << "'\n";
  int best_polymer = 50000;
  for (char i = 'a'; i <= 'z'; i++)
    best_polymer = std::min<>(test_polymer(i, polymer), best_polymer);
  std::cout << "Polymer length is " << best_polymer << '\n';
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
