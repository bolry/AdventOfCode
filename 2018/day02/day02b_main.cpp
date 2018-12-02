#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <map>
#include <vector>

namespace {
typedef std::vector<std::string> StrVec;
}

int main(int argc, char *argv[])
try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("Need input data filename\n");
  std::ifstream id_file(argv[1]);
  if (!id_file) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
  std::istream_iterator<std::string> id_reader(id_file);
  std::istream_iterator<std::string> id_reader_EOF;
  StrVec ids;
  std::copy(id_reader, id_reader_EOF, std::back_insert_iterator<StrVec>(ids));
  std::sort(ids.begin(), ids.end());
  std::string first;
  std::string next;
  for (int i = 1; i < ids.size(); i++) {
    first = ids[i - 1];
    next = ids[i];
    auto diff = std::mismatch(first.begin(), first.end(), next.begin());
    first.erase(diff.first);
    next.erase(diff.second);
    if (first == next) break;
  }
  std::cout << first << '\n' << std::flush;
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
