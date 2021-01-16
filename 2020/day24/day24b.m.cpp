#include <algorithm>
#include <array>
#include <compare>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_map>

#include <boost/container_hash/hash.hpp>

namespace
{
struct DoubledCoord
{
   int col;
   int row;
   friend auto operator<=>(DoubledCoord const&, DoubledCoord const&) noexcept =
      default;
};

// clang-format off
enum Direction : int { E, NE, NW, W, SW, SE, DirectionMax = SE };
// clang-format on

constexpr DoubledCoord doubleWidthNeighbor(
   DoubledCoord const& hex,
   Direction direction) noexcept
{
   constexpr std::array<std::array<int, 2>, 6> kDoubleWidthDirections{
      {{{+2, 0}}, {{+1, +1}}, {{-1, +1}}, {{-2, 0}}, {{-1, -1}}, {{+1, -1}}}};
   auto const dir = kDoubleWidthDirections[direction];
   return {hex.col + dir[0], hex.row + dir[1]};
}

constexpr void operator++(Direction& dir) noexcept
{
   dir = static_cast<Direction>(
      static_cast<std::underlying_type_t<Direction>>(dir) + 1);
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

namespace
{
enum class TileColor : bool
{
   white,
   black,
};
using FloorMap = std::unordered_map<DoubledCoord, TileColor>;

int cntBlackTileNeighbors(DoubledCoord hex, FloorMap const& tileFloor)
{
   int blackTileNeighbors{};
   auto const end = cend(tileFloor);
   for(Direction dir{}; dir < DirectionMax; ++dir)
   {
      auto neighborHex = doubleWidthNeighbor(hex, dir);
      if(auto iter = tileFloor.find(neighborHex);
         iter != end && iter->second == TileColor::black)
         ++blackTileNeighbors;
   }
   return blackTileNeighbors;
}
FloorMap expandFloor(FloorMap const& floor)
{
   auto bigger = floor;
   for(auto const& tile : floor)
   {
      for(Direction dir{}; dir < DirectionMax; ++dir)
      {
         bigger[doubleWidthNeighbor(tile.first, dir)];
      }
   }
   return bigger;
}
FloorMap dailyFlip(FloorMap oldFloor)
{
   oldFloor      = expandFloor(oldFloor);
   auto newFloor = oldFloor;
   for(auto const& tile : oldFloor)
   {
      auto nrBlackTileNeighbors = cntBlackTileNeighbors(tile.first, oldFloor);
      if(tile.second == TileColor::black &&
         (nrBlackTileNeighbors == 0 || nrBlackTileNeighbors > 2))
         newFloor[tile.first] = TileColor::white;
      else if(tile.second == TileColor::white && nrBlackTileNeighbors == 2)
         newFloor[tile.first] = TileColor::black;
      else
         newFloor[tile.first];
   }
   return newFloor;
}

}  // namespace

int main()
{
   FloorMap tileFloor;
   std::ifstream in("../input2.txt");
   std::string line;
   while(std::getline(in, line))
   {
      DoubledCoord hex{};
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
         hex = doubleWidthNeighbor(hex, dir);
      }
      if(auto& color = tileFloor[hex]; color == TileColor::white)
         color = TileColor::black;
      else
         color = TileColor::white;
   }
   auto nrOfBlackTiles = [](auto const& floor) {
      return std::ranges::count_if(
         floor, [](auto& tile) { return tile.second == TileColor::black; });
   };
   std::cout << "Day 0: " << nrOfBlackTiles(tileFloor) << '\n';
   for(int day{}; day < 10; ++day)
   {
      tileFloor = dailyFlip(tileFloor);
      std::cout << "Day " << day + 1 << ": " << nrOfBlackTiles(tileFloor)
                << '\n';
   }
   std::cout << nrOfBlackTiles(tileFloor) << " tiles with black side up.\n"
             << std::flush;
}
