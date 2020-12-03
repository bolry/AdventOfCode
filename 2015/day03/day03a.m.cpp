#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <unordered_set>

namespace
{
struct Pos
{
   std::uintmax_t x;
   std::uintmax_t y;
   friend bool operator==(Pos const& lhs, Pos const& rhs)
   {
      return lhs.x == rhs.x && lhs.y == rhs.y;
   }
};
}  // namespace
namespace std
{
template <>
struct hash<Pos>
{
   std::size_t operator()(Pos const& pos) const noexcept
   {
      constexpr auto h = std::hash<std::uintmax_t>{};
      std::size_t seed = h(pos.x) + 0x9e3779b9u;
      seed ^= h(pos.y) + 0x9e3779b9u + (seed << 6) + (seed >> 2);
      return seed;
   }
};
}  // namespace std
int main()
{
   std::ifstream in("../input.txt");
   std::unordered_set<Pos> houses;
   Pos santaPos{};
   houses.insert(santaPos);
   std::for_each(
      std::istream_iterator<char>(in),
      std::istream_iterator<char>(),
      [&santaPos, &houses](char ch) {
         auto& pos = santaPos;
         switch(ch)
         {
         case '^':
            ++pos.y;
            break;
         case 'v':
            --pos.y;
            break;
         case '>':
            ++pos.x;
            break;
         case '<':
            --pos.x;
            break;
         default:
            assert(false);
         }
         (void) houses.insert(pos);
      });
   std::cout << "At least " << size(houses)
             << " houses receive at least one present\n"
             << std::flush;
}
