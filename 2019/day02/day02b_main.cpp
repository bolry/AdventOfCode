#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <string>
#include <vector>

namespace {

using Int = int;
using Memory = std::vector<Int>;

struct CtypeWithWhitespaceComma : std::ctype<char> {
  static auto makeTable() {
    static std::vector v(classic_table(), classic_table() + table_size);
    v[','] |= space;
    return v.data();
  }
  explicit CtypeWithWhitespaceComma(size_t refs = 0U)
      : ctype(makeTable(), false, refs) {}
};

void add(Memory &memory, int &address) {
  std::array<Int, 3> const parameters{memory[address + 1], memory[address + 2],
                                      memory[address + 3]};
  Int const &readPositionA = memory[parameters[0]];
  Int const &readPositionB = memory[parameters[1]];
  Int &writePosition = memory[parameters[2]];

  writePosition = readPositionA + readPositionB;

  address += 4;
}

void multiply(Memory &memory, int &address) {
  std::array<Int, 3> const parameters{memory[address + 1], memory[address + 2],
                                      memory[address + 3]};
  Int const &readPositionA = memory[parameters[0]];
  Int const &readPositionB = memory[parameters[1]];
  Int &writePosition = memory[parameters[2]];

  writePosition = readPositionA * readPositionB;

  address += 4;
}

enum class OpCode {
  Unknown = 0,
  Add = 1,
  Multiply = 2,
  Halt = 99,
};

void runIntcodeProgram(Memory &memory) {
  for (int address = 0;;) {
    switch (auto const opcode = OpCode(memory[address]); opcode) {
    case OpCode::Add:
      add(memory, address);
      break;
    case OpCode::Multiply:
      multiply(memory, address);
      break;
    case OpCode::Halt:
      return;
    case OpCode::Unknown:
    default:
      throw std::runtime_error("Unknown opcode value " +
                               std::to_string(int(opcode)));
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
  Memory const memoryOnFile = [argv] {
    std::ifstream inFile(argv[1]);
    if (!inFile) {
      throw std::runtime_error("problem opening file " + std::string(argv[1]));
    }
    inFile.imbue(std::locale(std::cin.getloc(), new CtypeWithWhitespaceComma));
    return Memory(std::istream_iterator<Memory::value_type>{inFile},
                  std::istream_iterator<Memory::value_type>{});
  }();

  Memory memory;

  Int noun{};
  Int verb{};

  Int constexpr targetValue = 19690720;

  for (noun = 0; noun < 100; ++noun) {
    for (verb = 0; verb < 100; ++verb) {
      memory = memoryOnFile;
      memory[1] = noun;
      memory[2] = verb;
      runIntcodeProgram(memory);

      if (memory[0] == targetValue) {
        goto exitDoubleLoop;
      }
    }
  }
exitDoubleLoop:
  std::cout << "With noun " << noun << " and verb " << verb << " for target "
            << targetValue << " is " << 100 * noun + verb << '\n'
            << std::flush;
  return EXIT_SUCCESS;
}
