#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>

namespace
{
using namespace std::literals;
struct Instruction
{
   std::string op{};
   int arg{};
   bool used{};
   friend std::istream& operator>>(std::istream& in, Instruction& instruction)
   {
      in >> instruction.op >> instruction.arg;
      instruction.used = false;
      return in;
   }
};

std::vector<Instruction> gProgram;

bool runProgram(std::vector<Instruction>& prog, int& accu)
{
   auto const outside = ssize(prog);
   for(int offset{}; offset != outside;)
   {
      if(prog[offset].used)
         return false;
      prog[offset].used = true;
      if(prog[offset].op == "acc"sv)
      {
         accu += prog[offset].arg;
         ++offset;
      }
      else if(prog[offset].op == "jmp"sv)
      {
         offset += prog[offset].arg;
      }
      else if(prog[offset].op == "nop"sv)
      {
         ++offset;
      }
      else
      {
         assert(false);
      }
   }
   return true;
}

}  // namespace

int main()
{
   std::ifstream in("../input.txt"s);
   gProgram.reserve(637);
   std::copy(
      std::istream_iterator<Instruction>(in),
      std::istream_iterator<Instruction>(),
      std::back_inserter(gProgram));
   std::vector<Instruction> prog;
   prog.reserve(size(gProgram));
   for(int i = 0, stop = ssize(gProgram); i < stop; ++i)
   {
      prog = gProgram;
      if(prog[i].op == "jmp"sv)
         prog[i].op = "nop"sv;
      else if(prog[i].op == "nop"sv)
         prog[i].op = "jmp"sv;
      else
         continue;
      int accu{};
      bool completed = runProgram(prog, accu);
      std::cout << "acc is at "sv << accu << '\n';
      if(completed)
         break;
   }
   std::cout << std::flush;
}
