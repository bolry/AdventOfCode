#include <array>
#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <type_traits>
#include <vector>

namespace {
struct CtypeWithWhitespaceComma : std::ctype<char> {
  static auto makeTable() {
    static std::vector v(classic_table(), classic_table() + table_size);
    v[','] |= space;
    return v.data();
  }
  explicit CtypeWithWhitespaceComma(size_t refs = 0U)
      : ctype(makeTable(), false, refs) {}
};

using Int = int;
using Memory = std::vector<Int>;
using ParamModes = std::bitset<3>;

ParamModes getParamModes(int value) {
  ParamModes res;
  res.set(0, value % 10);
  value /= 10;
  res.set(1, value % 10);
  value /= 10;
  res.set(2, value % 10);
  return res;
}

void add(Memory &memory, int &address, ParamModes const paramModes) {
  std::array<Int, 3> const parameters{memory[address + 1], memory[address + 2],
                                      memory[address + 3]};
  Int const readPositionA =
      paramModes[0] ? parameters[0] : memory[parameters[0]];
  Int const readPositionB =
      paramModes[1] ? parameters[1] : memory[parameters[1]];
  Int &writePosition = memory[parameters[2]];

  writePosition = readPositionA + readPositionB;

  address += 4;
}

void multiply(Memory &memory, int &address, ParamModes const paramModes) {
  std::array<Int, 3> const parameters{memory[address + 1], memory[address + 2],
                                      memory[address + 3]};
  Int const readPositionA =
      paramModes[0] ? parameters[0] : memory[parameters[0]];
  Int const readPositionB =
      paramModes[1] ? parameters[1] : memory[parameters[1]];
  Int &writePosition = memory[parameters[2]];

  writePosition = readPositionA * readPositionB;

  address += 4;
}

void input(Memory &memory, int &address, ParamModes) {
  Int const parameter = memory[address + 1];

  Int &inputPosition = memory[parameter];

  inputPosition = 5;

  address += 2;
}

void output(Memory &memory, int &address, ParamModes const paramModes) {
  Int const parameter = memory[address + 1];

  Int const outputPosition = paramModes[0] ? parameter : memory[parameter];

  std::cout << outputPosition << '\n';

  address += 2;
}

void jumpIfTrue(Memory &memory, int &address, ParamModes const paramModes) {
  std::array<Int, 2> const parameters{memory[address + 1], memory[address + 2]};
  if (Int const readPositionA =
          paramModes[0] ? parameters[0] : memory[parameters[0]];
      readPositionA != 0) {
    Int const readPositionB =
        paramModes[1] ? parameters[1] : memory[parameters[1]];
    address = readPositionB;
  } else {
    address += 3;
  }
}

void jumpIfFalse(Memory &memory, int &address, ParamModes const paramModes) {
  std::array<Int, 2> const parameters{memory[address + 1], memory[address + 2]};
  if (Int const readPositionA =
          paramModes[0] ? parameters[0] : memory[parameters[0]];
      readPositionA == 0) {
    Int const readPositionB =
        paramModes[1] ? parameters[1] : memory[parameters[1]];
    address = readPositionB;
  } else {
    address += 3;
  }
}

void lessThan(Memory &memory, int &address, ParamModes const paramModes) {
  std::array<Int, 3> const parameters{memory[address + 1], memory[address + 2],
                                      memory[address + 3]};
  Int const readPositionA =
      paramModes[0] ? parameters[0] : memory[parameters[0]];
  Int const readPositionB =
      paramModes[1] ? parameters[1] : memory[parameters[1]];
  Int &writePosition = memory[parameters[2]];

  writePosition = (readPositionA < readPositionB);

  address += 4;
}

void equals(Memory &memory, int &address, ParamModes const paramModes) {
  std::array<Int, 3> const parameters{memory[address + 1], memory[address + 2],
                                      memory[address + 3]};
  Int const readPositionA =
      paramModes[0] ? parameters[0] : memory[parameters[0]];
  Int const readPositionB =
      paramModes[1] ? parameters[1] : memory[parameters[1]];
  Int &writePosition = memory[parameters[2]];

  writePosition = (readPositionA == readPositionB);

  address += 4;
}

enum class OpCode {
  Unknown = 0,
  Add = 1,
  Multiply = 2,
  Input = 3,
  Output = 4,
  JumpIfTrue = 5,
  JumpIfFalse = 6,
  LessThan = 7,
  Equals = 8,
  Halt = 99,
};

OpCode getOpCode(int const value) { return static_cast<OpCode>(value); }

void runIntcodeProgram(Memory &memory) {
  for (int address = 0;;) {
    auto const div = std::div(memory[address], 100);
    auto const paramModes = getParamModes(div.quot);
    switch (getOpCode(div.rem)) {
    case OpCode::Add:
      add(memory, address, paramModes);
      break;
    case OpCode::Multiply:
      multiply(memory, address, paramModes);
      break;
    case OpCode::Input:
      input(memory, address, paramModes);
      break;
    case OpCode::Output:
      output(memory, address, paramModes);
      break;
    case OpCode::JumpIfTrue:
      jumpIfTrue(memory, address, paramModes);
      break;
    case OpCode::JumpIfFalse:
      jumpIfFalse(memory, address, paramModes);
      break;
    case OpCode::LessThan:
      lessThan(memory, address, paramModes);
      break;
    case OpCode::Equals:
      equals(memory, address, paramModes);
      break;
    case OpCode::Halt:
      return;
    case OpCode::Unknown:
    default:
      throw std::runtime_error("Unknown opcode value " +
                               std::to_string(div.rem));
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
  Memory memoryOnFile = [argv] {
    if (std::ifstream inFile(argv[1]); inFile) {
      inFile.imbue(
          std::locale(std::cin.getloc(), new CtypeWithWhitespaceComma));
      return Memory(std::istream_iterator<Memory::value_type>{inFile},
                    std::istream_iterator<Memory::value_type>{});
    }
    throw std::runtime_error("problem opening file " + std::string(argv[1]));
  }();

  runIntcodeProgram(memoryOnFile);

  return EXIT_SUCCESS;
}
