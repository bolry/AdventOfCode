#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <new>
#include <string>
#include <vector>

namespace {

}

int main(int argc, char *argv[])
try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("Need input data filename\n");
  std::ifstream claim_file(argv[1]);
  if (!claim_file) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
  std::istream_iterator<Claim> claim_reader(claim_file);
  std::istream_iterator<Claim> claim_reader_EOF;
  std::cout << "Result day 4 B\n" << std::flush;
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
