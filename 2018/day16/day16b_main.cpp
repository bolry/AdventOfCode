#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void set_ostream_exceptions(std::ostream &o) { o.exceptions(o.badbit | o.eofbit | o.failbit); }

using Registers = std::array<int, 4>;
using Instruction = std::array<int, 4>;

enum class opcode {
  eqri = 0,
  mulr = 1,
  gtri = 2,
  gtrr = 3,
  banr = 4,
  addi = 5,
  seti = 6,
  gtir = 7,
  muli = 8,
  bori = 9,
  setr = 10,
  addr = 11,
  bani = 12,
  borr = 13,
  eqir = 14,
  eqrr = 15
};

Registers execute(opcode const oc, int const A, int const B, int const C, Registers const &regs) {
  Registers res = regs;
  switch (oc) {
    case opcode::addr: res.at(C) = regs.at(A) + regs.at(B);
      break;
    case opcode::addi: res.at(C) = regs.at(A) + B;
      break;
    case opcode::mulr: res.at(C) = regs.at(A) * regs.at(B);
      break;
    case opcode::muli: res.at(C) = regs.at(A) * B;
      break;
    case opcode::banr: res.at(C) = regs.at(A) & regs.at(B);
      break;
    case opcode::bani: res.at(C) = regs.at(A) & B;
      break;
    case opcode::borr: res.at(C) = regs.at(A) | regs.at(B);
      break;
    case opcode::bori: res.at(C) = regs.at(A) | B;
      break;
    case opcode::setr: res.at(C) = regs.at(A);
      break;
    case opcode::seti: res.at(C) = A;
      break;
    case opcode::gtir: res.at(C) = A > regs.at(B);
      break;
    case opcode::gtri: res.at(C) = regs.at(A) > B;
      break;
    case opcode::gtrr: res.at(C) = regs.at(A) > regs.at(B);
      break;
    case opcode::eqir: res.at(C) = A == regs.at(B);
      break;
    case opcode::eqri: res.at(C) = regs.at(A) == B;
      break;
    case opcode::eqrr: res.at(C) = regs.at(A) == regs.at(B);
      break;
  }
  return res;
}

std::istream &read_inst(std::istream &fin, Instruction &inst) {
  for (auto &i : inst)
    if (fin >> i, !fin) return fin;
  return fin;
}

}  // close anonymous namespace
int main(int argc, char *argv[]) {
  set_ostream_exceptions(std::cout);
  if (argc < 2) throw std::runtime_error("need filename argument");
  std::ifstream in_file(argv[1]);
  if (!in_file) throw std::runtime_error("Problem opening file " + std::string(argv[1]));
  bool prev_line_empty = false;
  std::string line;
  while (std::getline(in_file, line)) {
    if (line.empty()) {
      if (prev_line_empty) break;
      prev_line_empty = true;
    } else prev_line_empty = false;
  }
  if (!in_file) throw std::runtime_error("hmm, expecting more input data");
  Registers regs = {};
  Instruction inst;
  while (read_inst(in_file, inst))
    regs = execute(static_cast<opcode>(inst[0]), inst[1], inst[2], inst[3], regs);
  std::cout << "Register 0 has value " << regs[0] << '\n';
  return EXIT_SUCCESS;
}
