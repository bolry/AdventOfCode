#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

namespace
{
struct slope
{
   int right;
   int down = 1;
};
}  // namespace

int getTrees(std::vector<std::string> const& map, int right, int down)
{
   int treeCnt{};
   int col{};
   for(int rowId = 0; rowId < ssize(map); rowId += down)
   {
      if(col >= ssize(map[rowId]))
      {
         col %= ssize(map[rowId]);
      }
      if(map[rowId][col] == '#')
      {
         ++treeCnt;
      }
      col += right;
   }
   return treeCnt;
}
int main()
{
   std::ifstream in("../input.txt");
   std::vector<std::string> map;
   map.reserve(323);
   std::copy(
      std::istream_iterator<std::string>(in),
      std::istream_iterator<std::string>(),
      std::back_inserter(map));
   std::array<slope, 5> slopes{{{1}, {3}, {5}, {7}, {1, 2}}};
   int answer = std::accumulate(
      cbegin(slopes), cend(slopes), 1, [&map](int a, slope const& b) {
         return a * getTrees(map, b.right, b.down);
      });
   std::cout << "Found " << answer << " trees\n" << std::flush;
   return EXIT_SUCCESS;
}
