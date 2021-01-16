#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>

#include <boost/container_hash/hash.hpp>

namespace
{
using Int     = int;
using IsBlack = bool;

struct DoubledCoord
{
   Int col;
   Int row;
   friend bool operator==(DoubledCoord const&, DoubledCoord const&) noexcept =
      default;
   friend std::istream& operator>>(std::istream& in, DoubledCoord& hex)
   {
      std::string line;
      if(std::getline(in, line))
      {
         hex = DoubledCoord{};
         std::istringstream iss(line);
         constexpr auto end = std::istreambuf_iterator<char>{};
         for(auto it = std::istreambuf_iterator<char>{iss}; it != end; ++it)
            switch(*it)
            {  // clang-format off
         case 'e': hex.col += 2; break;
         case 'w': hex.col -= 2; break;
         case 'n': hex.col += 1 - 2 * (*++it == 'w'); hex.row += 1; break;
         case 's': hex.col += 1 - 2 * (*++it == 'w'); hex.row -= 1; break;
            }  // clang-format on
      }
      return in;
   }
};

}  // namespace

namespace std
{
template <>
struct hash<DoubledCoord>
{
   std::size_t operator()(DoubledCoord const& dc) const noexcept
   {
      std::size_t seed{0xA9B7'36E6'3C3D'FA42u};
      boost::hash_combine(seed, dc.col);
      boost::hash_combine(seed, dc.row);
      return seed;
   }
};
}  // namespace std

int main()
{
   std::ifstream in("../input.txt");
   std::unordered_map<DoubledCoord, IsBlack> tiles;
   std::istream_iterator<DoubledCoord> e{};
   for(std::istream_iterator<DoubledCoord> f{in}; f != e; ++f)
   {
      auto& isBlack = tiles[*f];
      isBlack       = !isBlack;
   }
   std::cout << std::ranges::count_if(tiles, [](auto const& pair) {
      return pair.second;  // isBlack
   }) << std::endl;
}
