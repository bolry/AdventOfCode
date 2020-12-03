#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

namespace
{
struct Slope
{
   std::size_t right{};
   std::size_t down{1u};
};
}  // namespace

std::uintmax_t getTrees(
   std::vector<std::string> const& map,
   std::size_t right,
   std::size_t down)
{
   std::uintmax_t treeCnt{};
   std::size_t col{};
   for(std::size_t rowId{0u}, rMax{size(map)}; rowId < rMax; rowId += down)
   {
      col %= size(map[rowId]);
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
   map.reserve(323u);
   std::copy(
      std::istream_iterator<std::string>(in),
      std::istream_iterator<std::string>(),
      std::back_inserter(map));
   std::array<Slope, 5u> slopes{{{1u}, {3u}, {5u}, {7u}, {1u, 2u}}};
   auto answer = std::accumulate(
      cbegin(slopes),
      cend(slopes),
      std::uintmax_t{1u},
      [&map](auto a, Slope const& b) {
         return a * getTrees(map, b.right, b.down);
      });
   std::cout << "Key multiplicative is " << answer << std::endl;
   return EXIT_SUCCESS;
}
