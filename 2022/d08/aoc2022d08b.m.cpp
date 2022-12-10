#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>

namespace
{
constexpr int kSize{99};  // known from my input data
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

int viewUp(int const x, int const y, Forest const& forest) noexcept
{
   int cnt{};
   auto const h = forest[y][x];
   for(int Y{y - 1}; Y >= 0; --Y)
   {
      ++cnt;
      if(forest[Y][x] >= h)
         break;
   }
   return cnt;
}
int viewDown(int const x, int const y, Forest const& forest) noexcept
{
   int cnt{};
   auto const h = forest[y][x];
   for(int Y{y + 1}; Y < kSize; ++Y)
   {
      ++cnt;
      if(forest[Y][x] >= h)
         break;
   }
   return cnt;
}
int viewLeft(int const x, int const y, Forest const& forest) noexcept
{
   int cnt{};
   auto const h = forest[y][x];
   for(int X{x - 1}; X >= 0; --X)
   {
      ++cnt;
      if(forest[y][X] >= h)
         break;
   }
   return cnt;
}
int viewRight(int const x, int const y, Forest const& forest) noexcept
{
   int cnt{};
   auto const h = forest[y][x];
   for(int X{x + 1}; X < kSize; ++X)
   {
      ++cnt;
      if(forest[y][X] >= h)
         break;
   }
   return cnt;
}

int scenicScore(int const x, int const y, Forest const& forest) noexcept
{
   int r1 = viewUp(x, y, forest);
   int r2 = viewDown(x, y, forest);
   int r3 = viewLeft(x, y, forest);
   int r4 = viewRight(x, y, forest);
   return r1 * r2 * r3 * r4;
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
      using OIter = std::ostream_iterator<char>;
      r4s::copy(r, OIter{std::cout});
      std::cout << "'\n";
   }
   int bestScenicScore{};
   for(int x{}; x != kSize; ++x)
   {
      for(int y{}; y != kSize; ++y)
      {
         bestScenicScore = r4s::max(bestScenicScore, scenicScore(x, y, forest));
      }
   }
   std::cout << "\nThe highest scenic score is " << bestScenicScore
             << std::endl;
   return EXIT_SUCCESS;
}
