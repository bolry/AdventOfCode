#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std::literals;
using namespace std::ranges;

namespace
{
enum Dir : char  // direction
{
   // clang-format off
   N = 'N', S = 'S', E = 'E', W = 'W',
   L = 'L', R = 'R',
   F = 'F'
   // clang-format on
};
struct Ship
{
   Dir currentDir = E;
   int posX{};  // east/west
   int posY{};  // north/south
};
struct Move
{
   Dir dir;
   int dist;
   friend std::istream& operator>>(std::istream& in, Move& mv)
   {
      char c;
      in >> c >> mv.dist;
      mv.dir = Dir{c};
      return in;
   }
};

Dir newDir(Dir const oldDir, Move const& mv)
{
   auto getAngle = [](Dir d) {
      switch(d)
      {
         // clang-format off
      case N: return 0;
      case S: return 180;
      case E: return 90;
      case W: return 270;
         // clang-format on
      }
   };
   int rotation = getAngle(oldDir) + 360;
   rotation += mv.dist * (mv.dir == R ? 1 : -1);
   switch(rotation %= 360)
   {
      // clang-format off
   case 0: return N;
   case 90: return E;
   case 180: return S;
   case 270: return W;
      // clang-format on
   }
}

void goForward(Ship& ship, Move const& mv)
{
   switch(ship.currentDir)
   {
      // clang-format off
   case N: ship.posY += mv.dist; break;
   case S: ship.posY -= mv.dist; break;
   case E: ship.posX += mv.dist; break;
   case W: ship.posX -= mv.dist; break;
      // clang-format on
   }
}
}  // namespace

int main()
{
   std::ifstream in("../input.txt"s);
   Ship ship{};
   for_each(
      std::istream_iterator<Move>{in},
      std::istream_iterator<Move>{},
      [&ship](Move const& mv) {
         switch(mv.dir)
         {
            // clang-format off
         case N: ship.posY += mv.dist; break;
         case S: ship.posY -= mv.dist; break;
         case E: ship.posX += mv.dist; break;
         case W: ship.posX -= mv.dist; break;
            // clang-format on
         case L:
         case R:
            ship.currentDir = newDir(ship.currentDir, mv);
            break;
         case F:
            goForward(ship, mv);
            break;
         }
      });
   std::cout << std::abs(ship.posX) + std::abs(ship.posY) << std::flush;
   return EXIT_SUCCESS;
}
