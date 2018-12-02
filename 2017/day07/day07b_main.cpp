#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <new>
#include <vector>

namespace {
struct Program;
typedef std::vector<Program> ChildPrograms;
struct Program {
  std::string name;
  int weight;
  ChildPrograms children;
};
std::istream &operator>>(std::istream &in, Program &prog) {
  return std::getline(in, prog.name);
}
std::ostream &operator<<(std::ostream &out, Program const &prog) {
  return out << "\"Name\": `" << prog.name << '\'';
}
}

int main(int argc, char *argv[]) try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("Sorry, program needs one command line argument");
  std::ifstream disc_data(argv[1]);
  if (!disc_data) throw std::runtime_error(std::string("Unable to open file `") + argv[1] + '\'');
  ChildPrograms all_progs;
  std::copy(std::istream_iterator<Program>(disc_data),
            std::istream_iterator<Program>(),
            std::back_insert_iterator<ChildPrograms>(all_progs));
  std::copy(all_progs.begin(), all_progs.end(), std::ostream_iterator<Program>(std::cout, "\n"));
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
