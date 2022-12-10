#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

namespace
{
using Int      = int;
using Register = Int;
struct Cpu
{
   Int cycle{};
   Register X{1};
   Int sum{};
   void calc()
   {
      if((cycle - 20) % 40 == 0)
      {
         sum += cycle * X;
         std::cout << cycle << " * " << X << " = " << cycle * X << '\n';
      }
   }
   void addx(Int valueV)
   {
      ++cycle;
      calc();
      ++cycle;
      calc();
      X += valueV;
   }
   void noop()
   {
      ++cycle;
      calc();
   }
};
}  // namespace

int main()
{
   Cpu cpu;
   std::ifstream ifs("../input.txt");
   assert(ifs);
   for(std::string cmd; ifs >> cmd;)
   {
      using namespace std::string_view_literals;
      if(cmd == "noop"sv)
         cpu.noop();
      else if(cmd == "addx"sv)
      {
         Int value;
         ifs >> value;
         assert(ifs);
         cpu.addx(value);
      }
      else
         assert(false);
   }
   std::cout << "\nThe sum is " << cpu.sum << std::endl;
   return EXIT_SUCCESS;
}
