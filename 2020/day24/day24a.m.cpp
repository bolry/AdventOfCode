#include <algorithm>
#include <array>
#include <compare>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

#include <boost/container_hash/hash.hpp>

namespace
{
// clang-format off
enum Direction { E, NE, NW, W, SW, SE };
// clang-format on
constexpr std::array<std::array<int, 2>, 6> kDoubleWidthDirections{
   {{+2, 0}, {+1, -1}, {-1, -1}, {-2, 0}, {-1, +1}, {+1, +1}}};

struct DoubledCoord
{
   int col;
   int row;
   friend bool operator==(DoubledCoord const&, DoubledCoord const&) = default;
};

constexpr DoubledCoord doubleWidthNeighbor(
   DoubledCoord hex,
   Direction direction) noexcept
{
   auto const dir = kDoubleWidthDirections[direction];
   return {hex.col + dir[0], hex.row + dir[1]};
}

}  // namespace

namespace std
{
template <>
struct hash<DoubledCoord>
{
   std::size_t operator()(DoubledCoord const& dc) const noexcept
   {
      std::size_t seed{};
      boost::hash_combine(seed, dc.col);
      boost::hash_combine(seed, dc.row);
      return seed;
   }
};
}  // namespace std

int main()
{
   enum class TileColor : bool
   {
      white,
      black,
   };
   std::unordered_map<DoubledCoord, TileColor> tileFloor;

   std::ifstream in("../input.txt");
   std::string line;
   while(std::getline(in, line))
   {
      DoubledCoord coord{};
      for(auto f = begin(line), l = end(line); f != l; ++f)
      {
         Direction dir;
         switch(*f)
         {
            // clang-format off
         case 'e': dir = E; break;
         case 'w': dir = W; break;
         case 'n': ++f; dir = *f == 'e' ? NE : NW; break;
         case 's': ++f; dir = *f == 'e' ? SE : SW; break;
            // clang-format on
         }
         coord = doubleWidthNeighbor(coord, dir);
      }
      if(auto& color = tileFloor[coord]; color == TileColor::white)
         color = TileColor::black;
      else
         color = TileColor::white;
   }

   std::cout << std::ranges::count_if(
                   tileFloor,
                   [](auto const& pair) {
                      return pair.second == TileColor::black;
                   })
             << " tiles with black side up.\n"
             << std::flush;
}
