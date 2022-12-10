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
   std::ostream& crtScreen;
   Int cycle{};
   Register X{1};
   void addx(Int valueV) noexcept
   {
      ++cycle;
      crtScreen << *this;
      ++cycle;
      crtScreen << *this;
      X += valueV;
   }
   void noop() noexcept
   {
      ++cycle;
      crtScreen << *this;
   }
   // report pixel output
   friend std::ostream& operator<<(std::ostream& os, Cpu const& cpu)
   {
      Int pos = (cpu.cycle - 1) % 40;
      os << ((pos < cpu.X - 1 or cpu.X + 1 < pos) ? ' ' : '#');
      if(pos == 39)
         os << '\n';
      return os;
   }
};
}  // namespace

int main()
{
   Cpu cpu{std::cout};
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
   return EXIT_SUCCESS;
}
