#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <new>
#include <sstream>
#include <vector>

namespace {

typedef std::vector<std::string> StrVec;

struct Program {
  std::string name;
  int weight;
  StrVec children_names;
};

std::istream &operator>>(std::istream &in, Program &prog) {
  prog.children_names.clear();
  std::string line;
  if (!std::getline(in, line)) return in;
  std::istringstream iss(line);
  char left_parenthesis = '\0';
  char right_parenthesis = '\0';
  iss >> prog.name >> left_parenthesis >> prog.weight >> right_parenthesis;
  if (!iss || left_parenthesis != '(' || right_parenthesis != ')') return in.setstate(in.failbit), in;
  std::string arrow;
  iss >> arrow;
  if (iss.eof()) return in;
  if (!iss || arrow != "->") return in.setstate(in.failbit), in;
  std::string child_name;
  while (iss >> child_name) {
    if (child_name.back() == ',') child_name.pop_back();
    prog.children_names.push_back(child_name);
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, Program const &prog) {
  return out << "Name: `" << prog.name << "' Weight: " << prog.weight << " NrChilds: " << prog.children_names.size();
}

}  // close anonymous namespace

int main(int argc, char *argv[]) try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("Sorry, program needs one command line argument");
  std::ifstream disc_data(argv[1]);
  if (!disc_data) throw std::runtime_error(std::string("Unable to open file `") + argv[1] + '\'');
  std::vector<Program> all_progs;
  std::copy(std::istream_iterator<Program>(disc_data),
            std::istream_iterator<Program>(),
            std::back_inserter(all_progs));
  std::for_each(all_progs.begin(), all_progs.end(), [&all_progs](Program &prog) {
    prog.children_names;
  });
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
