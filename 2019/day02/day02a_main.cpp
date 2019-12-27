#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <vector>

namespace {

struct CtypeWithWhitespaceComma : std::ctype<char> {
  static mask const *makeTable() {
    static std::vector<mask> v(classic_table(), classic_table() + table_size);
    v[','] |= space;
    return &v[0];
  }
  CtypeWithWhitespaceComma(size_t refs = 0U) : ctype(makeTable(), false, refs) {}
};

void runIntcodeProgram(std::vector<int> &memory) {
  for (int pos = 0;;) {
    switch (memory[pos]) {
    case 1: {
      int const leftPos = memory[pos + 1];
      int const rightPos = memory[pos + 2];
      int const resPos = memory[pos + 3];
      memory[resPos] = memory[leftPos] + memory[rightPos];
      pos += 4;
    } break;
    case 2: {
      int const leftPos = memory[pos + 1];
      int const rightPos = memory[pos + 2];
      int const resPos = memory[pos + 3];
      memory[resPos] = memory[leftPos] * memory[rightPos];
      pos += 4;
    } break;
    case 99:
      return;
    default:
      throw std::runtime_error("");
    }
  }
}

} // namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::ios_base::badbit | std::ios_base::eofbit |
                       std::ios_base::failbit);
  if (argc < 2) {
    throw std::runtime_error("need filename argument");
  }
  std::ifstream inFile(argv[1]);
  if (!inFile) {
    throw std::runtime_error("problem opening file " + std::string(argv[1]));
  }
  inFile.imbue(std::locale(std::cin.getloc(), new CtypeWithWhitespaceComma));
  std::vector<int> v(std::istream_iterator<int>{inFile},
                     std::istream_iterator<int>{});

  v[1] = 12;
  v[2] = 2;

  runIntcodeProgram(v);

  std::cout << "The value at position 0 is " << v[0] << '\n' << std::flush;
  return EXIT_SUCCESS;
}
