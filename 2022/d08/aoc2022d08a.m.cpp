#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>

namespace
{
constexpr int kSize{99};
using Row    = std::array<char, kSize>;
using Forest = std::array<Row, kSize>;

namespace r4s = std::ranges;

Forest readForest(std::istream& in) noexcept
{
   Forest forest;
   for(int r{}; r != kSize; ++r)
   {
      using Iter = std::istreambuf_iterator<char>;
      r4s::copy_n(Iter{in}, kSize, forest[r].begin());
      in.ignore();
   }
   return forest;
}
bool isHiddenUp(int const x, int const y, Forest const& forest) noexcept
{
   if(y == 0)
      return false;
   auto const h = forest[y][x];
   for(int Y{}; Y != y; ++Y)
      if(forest[Y][x] >= h)
         return true;
   return false;
}
bool isHiddenDown(int const x, int const y, Forest const& forest) noexcept
{
   if(y == kSize - 1)
      return false;
   auto const h = forest[y][x];
   for(int Y{y + 1}; Y != kSize; ++Y)
      if(forest[Y][x] >= h)
         return true;
   return false;
}
bool isHiddenLeft(int const x, int const y, Forest const& forest) noexcept
{
   if(x == 0)
      return false;
   auto const h = forest[y][x];
   for(int X{}; X != x; ++X)
      if(forest[y][X] >= h)
         return true;
   return false;
}
bool isHiddenRight(int const x, int const y, Forest const& forest) noexcept
{
   if(x == kSize - 1)
      return false;
   auto const h = forest[y][x];
   for(int X{x + 1}; X != kSize; ++X)
      if(forest[y][X] >= h)
         return true;
   return false;
}

bool isVisible(int const x, int const y, Forest const& forest) noexcept
{
   if(isHiddenUp(x, y, forest) and isHiddenDown(x, y, forest) and
      isHiddenLeft(x, y, forest) and isHiddenRight(x, y, forest))
      return false;
   else
      return true;
}

}  // namespace

int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);
   auto forest = readForest(ifs);
   for(auto const& r : forest)
   {
      std::cout << '`';
      r4s::copy(r, std::ostream_iterator<char>{std::cout});
      std::cout << "'\n";
   }
   int cntVisible{};
   for(int x{}; x != kSize; ++x)
   {
      for(int y{}; y != kSize; ++y)
      {
         if(isVisible(x, y, forest))
            ++cntVisible;
      }
   }
   std::cout << "The number of visible trees " << cntVisible << '\n';
   return EXIT_SUCCESS;
}
