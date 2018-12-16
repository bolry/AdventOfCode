#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace {

void set_ostream_exceptions(std::ostream &o) { o.exceptions(o.badbit | o.eofbit | o.failbit); }

using Registers = std::array<int, 4>;
using Instruction = std::array<int, 4>;

std::ostream &pr_regs(std::ostream &fout, Registers const &regs) {
  return fout << "R[0]: " << regs[0] << " R[1]: " << regs[1] << " R[2]: " << regs[2] << " R[3]: " << regs[3];
}

std::ostream &pr_inst(std::ostream &fout, Instruction const &inst) {
  return fout << "opcode: " << inst[0] << " [A]: " << inst[1] << " [B]: " << inst[2] << " [C]: " << inst[3];
}

enum class opcode {
  addr, addi,
  mulr, muli,
  banr, bani,
  borr, bori,
  setr, seti,
  gtir, gtri, gtrr,
  eqir, eqri, eqrr
};

opcode& operator++(opcode& oc){
  if(oc == opcode::eqrr) oc = opcode::addr;
  else oc = static_cast<opcode>(std::underlying_type_t<opcode>(oc) + 1);
  return oc;
}

Registers execute(opcode const oc, int const A, int const B, int const C, Registers const &regs) {
  Registers res = regs;
  switch (oc) {
    case opcode::addr: res.at(C) = regs.at(A) + regs.at(B); break;
    case opcode::addi: res.at(C) = regs.at(A) + B; break;
    case opcode::mulr: res.at(C) = regs.at(A) * regs.at(B); break;
    case opcode::muli: res.at(C) = regs.at(A) * B; break;
    case opcode::banr: res.at(C) = regs.at(A) & regs.at(B); break;
    case opcode::bani: res.at(C) = regs.at(A) & B; break;
    case opcode::borr: res.at(C) = regs.at(A) | regs.at(B); break;
    case opcode::bori: res.at(C) = regs.at(A) | B; break;
    case opcode::setr: res.at(C) = regs.at(A); break;
    case opcode::seti: res.at(C) = A; break;
    case opcode::gtir: res.at(C) = A > regs.at(B); break;
    case opcode::gtri: res.at(C) = regs.at(A) > B; break;
    case opcode::gtrr: res.at(C) = regs.at(A) > regs.at(B); break;
    case opcode::eqir: res.at(C) = A == regs.at(B); break;
    case opcode::eqri: res.at(C) = regs.at(A) == B; break;
    case opcode::eqrr: res.at(C) = regs.at(A) == regs.at(B); break;
  }
  return res;
}
static std::unordered_map<std::string, opcode> const Str2Opcode = {
    {"addr", opcode::addr},
    {"addi", opcode::addi},
    {"mulr", opcode::mulr},
    {"muli", opcode::muli},
    {"banr", opcode::banr},
    {"bani", opcode::bani},
    {"borr", opcode::borr},
    {"bori", opcode::bori},
    {"setr", opcode::setr},
    {"seti", opcode::seti},
    {"gtir", opcode::gtir},
    {"gtri", opcode::gtri},
    {"gtrr", opcode::gtrr},
    {"eqir", opcode::eqir},
    {"eqri", opcode::eqri},
    {"eqrr", opcode::eqrr}
};
Registers execute(std::string const& oc, int const A, int const B, int const C, Registers const &regs) {
  return execute(Str2Opcode.at(oc), A, B, C, regs);
}
struct Sample {
  Registers before_regs;
  Instruction instruction;
  Registers after_regs;
};

std::istream &operator>>(std::istream &fin, Sample &sample) {
  std::string token;
  if (!(fin >> token)) return fin;
  if (token != "Before:") return fin.setstate(fin.failbit), fin;
  char ch;
  fin >> ch >> sample.before_regs[0] >> ch >> sample.before_regs[1] >> ch >> sample.before_regs[2] >> ch
      >> sample.before_regs[3] >> ch;
  if (!fin) return fin;
  if (ch != ']') return fin.setstate(fin.failbit), fin;
  for (auto &i : sample.instruction)
    if (fin >> i, !fin) return fin;
  if (!(fin >> token)) return fin;
  if (token != "After:") return fin.setstate(fin.failbit), fin;
  fin >> ch >> sample.after_regs[0] >> ch >> sample.after_regs[1] >> ch >> sample.after_regs[2] >> ch
      >> sample.after_regs[3] >> ch;
  if (!fin) return fin;
  if (ch != ']') fin.setstate(fin.failbit);
  return fin;
}

std::ostream &operator<<(std::ostream &os, Sample const &sample) {
  return os << "before_regs: ", pr_regs(os, sample.before_regs) << "\ninstruction: ", pr_inst(os, sample.instruction)
      << "\nafter_regs: "
      , pr_regs(os, sample.after_regs);
}

bool behaves_like(std::string const &opcode, Sample const &sample) {
  return true;
}

}  // close anonymous namespace
int main(int argc, char *argv[]) {
  set_ostream_exceptions(std::cout);
  if (argc < 2) throw std::runtime_error("need filename argument");
  std::ifstream in_file(argv[1]);
  if (!in_file) throw std::runtime_error("Problem opening file " + std::string(argv[1]));
  std::istream_iterator<Sample> const sample_reader_EOF;
  int tot_count = 0;
  for (std::istream_iterator<Sample> sample_reader(in_file); sample_reader != sample_reader_EOF; ++sample_reader) {
    int similar_count = 0;
    Sample const &sam = *sample_reader;
    opcode oc = static_cast<opcode>(0);
    do {
      if (sam.after_regs == execute(oc, sam.instruction[1], sam.instruction[2], sam.instruction[3], sam.before_regs))
        similar_count++;
    } while (++oc != static_cast<opcode>(0));
    std::cout << "Similars: " << similar_count << '\n';
    if(similar_count >= 3) tot_count++;
  }
  std::cout << "Number with three or more similar " << tot_count <<'\n';
  return EXIT_SUCCESS;
}
