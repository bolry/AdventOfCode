#include <algorithm>
#include <complex>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

using namespace std::ranges;

namespace
{
using Pos = std::complex<int>;

constexpr Pos operator""_i(unsigned long long int imag)
{
   return {0, imag};
}

enum Dir : char  // direction
{
   N = 'N',
   S = 'S',
   E = 'E',
   W = 'W',
   L = 'L',
   R = 'R',
   F = 'F',
};

struct Ship
{
   Dir currentDir{E};
   Pos pos{};
   Pos waypoint{10, 1};
};

struct Move
{
   Dir dir;
   int val;
   friend std::istream& operator>>(std::istream& in, Move& mv)
   {
      char c;
      in >> c >> mv.val;
      mv.dir = Dir{c};
      return in;
   }
};

void mvFwdBy(Ship& ship, int const val)
{
   ship.pos += static_cast<Pos::value_type>(val) * ship.waypoint;
}

void mvPos(Pos& pos, Move const& move)
{
   switch(move.dir)
   {
      // clang-format off
   case N: pos += Pos{0, move.val}; break;
   case S: pos -= Pos{0, move.val}; break;
   case E: pos += move.val; break;
   case W: pos -= move.val; break;
      // clang-format on
   }
}

void rotClockwise(Pos& pos, int const degrees)
{
   switch(degrees)
   {
   case 90:
   case -270:
      pos *= -1_i;
      break;
   case -180:
   case 180:
      pos *= -1;
      break;
   case -90:
   case 270:
      pos *= 1_i;
      break;
   }
}

auto manhattanDistance(Pos const& pos)
{
   return std::abs(pos.real()) + std::abs(pos.imag());
}

}  // namespace

int main()
{
   Ship ship;
#if 1
   std::ifstream in("../input.txt");
#else
   std::istringstream in("F10 N3 F7 R90 F11");
#endif
   for_each(
      std::istream_iterator<Move>{in},
      std::istream_iterator<Move>{},
      [&ship](Move const& mv) {
         switch(mv.dir)
         {
         case N:
         case S:
         case E:
         case W:
            mvPos(ship.waypoint, mv);
            break;
         case L:
            rotClockwise(ship.waypoint, -mv.val);
            break;
         case R:
            rotClockwise(ship.waypoint, mv.val);
            break;
         case F:
            mvFwdBy(ship, mv.val);
            break;
         }
      });
   std::cout << manhattanDistance(ship.pos) << std::flush;
   return EXIT_SUCCESS;
}
