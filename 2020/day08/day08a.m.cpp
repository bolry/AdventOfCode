#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
namespace
{
using namespace std::literals;
using namespace std::ranges;
struct Instruction
{
   std::string op{};
   int arg{};
   bool used{};
   friend std::istream& operator>>(std::istream& in, Instruction& instruction)
   {
      in >> instruction.op >> instruction.arg;
      instruction.used=false;
      return in;
   }
};

int gAccu{};

std::vector<Instruction> gProgram;

void runProgram(){
   for(int offset{}; !gProgram[offset].used;){
      gProgram[offset].used = true;
      if(gProgram[offset].op == "acc"sv){
         gAccu += gProgram[offset].arg;
         ++offset;
      }else if(gProgram[offset].op == "jmp"sv){
         offset += gProgram[offset].arg;
      } if(gProgram[offset].op == "nop"sv){
         ++offset;
      }else{}
   }
}

}  // namespace

int main()
{
   std::ifstream in("../input.txt"s);
   gProgram.reserve(637);
   copy(
      std::istream_iterator<Instruction>(in),
      std::istream_iterator<Instruction>(),
      std::back_inserter(gProgram));
   runProgram();
   std::cout << "acc is at "sv << gAccu << std::endl;
}
