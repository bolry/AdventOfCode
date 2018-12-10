#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <new>
#include <set>
#include <string>
#include <vector>

namespace {
struct Instruct {
  char before;
  char after;
};
std::istream &operator>>(std::istream &fin, Instruct &order) {
  std::string line;
  if (std::getline(fin, line)) {
    order.before = line[5];
    order.after = line[36];
  }
  return fin;
}
std::ostream &operator<<(std::ostream &fout, Instruct const &order) {
  return fout << order.before << " -> " << order.after;
}
}

int main(int argc, char *argv[])
try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("Need input data filename\n");
  std::ifstream instruct_file(argv[1]);
  if (!instruct_file) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
  std::vector<Instruct> instructions;
  std::istream_iterator<Instruct> instruct_reader(instruct_file);
  std::istream_iterator<Instruct> instruct_reader_EOF;
  std::copy(instruct_reader, instruct_reader_EOF, std::back_inserter(instructions));
  std::copy(instructions.begin(), instructions.end(), std::ostream_iterator<Instruct>(std::cout, "\n"));
  std::vector<char> firsts;
  std::vector<char> seconds;
  std::vector<char> diff;
  std::vector<int> busy_workers;
  int timeline = 0;
  while (!instructions.empty()) {
    firsts.clear();
    std::transform(instructions.begin(), instructions.end(), std::back_inserter(firsts), [](Instruct const &in) {
      return in.before;
    });
    std::sort(firsts.begin(), firsts.end());
    firsts.erase(std::unique(firsts.begin(), firsts.end()), firsts.end());
    seconds.clear();
    std::transform(instructions.begin(), instructions.end(), std::back_inserter(seconds), [](Instruct const &in) {
      return in.after;
    });
    std::sort(seconds.begin(), seconds.end());
    seconds.erase(std::unique(seconds.begin(), seconds.end()), seconds.end());
    diff.clear();
    std::set_difference(firsts.begin(), firsts.end(), seconds.begin(), seconds.end(), std::back_inserter(diff));
    std::cout << ' '; std::copy(diff.begin(),diff.end(), std::ostream_iterator<char>(std::cout, "")); std::cout << '\n';
    char const next = diff.front();
    std::cout << next;
    if (instructions.size() == 1U) std::cout << instructions.back().after << '\n';
    instructions.erase(std::remove_if(instructions.begin(),
                                      instructions.end(),
                                      [&next](Instruct const &in) { return in.before == next; }), instructions.end());
  }
  std::cout << "Day 7 B result is " << timeline << " seconds\n";
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
