#include <cassert>
#include <charconv>
#include <compare>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>

namespace
{
struct Pos
{
   int x;
   int y;
   friend bool operator==(const Pos& lhs, const Pos& rhs)
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
   size_t operator()(Pos const& s) const noexcept
   {
      size_t h1 = hash<int>{}(s.x);
      size_t h2 = hash<int>{}(s.y);
      return h1 ^ (h2 << 1);
   }
};
}  // namespace std

namespace
{
using Set = std::unordered_set<Pos>;
std::array<Pos, 10> rope{};
Set tailPos{rope.back()};
bool adjustTail(Pos a_head, Pos& ar_tail) noexcept
{
   int const dx = a_head.x - ar_tail.x;
   int const dy = a_head.y - ar_tail.y;
   if(std::abs(dx) <= 1 and std::abs(dy) <= 1)
      return false;
   if(dy == 0)
   {
      // T.H -> .TH
      // H.T -> HT.
      ar_tail.x += dx / 2;
   }
   else if(dx == 0)
   {
      ar_tail.y += dy / 2;
   }
   else if(std::abs(dy) == 1)
   {
      ar_tail.x += dx / 2;
      ar_tail.y += dy;
   }
   else if(std::abs(dx) == 1)
   {
      ar_tail.x += dx;
      ar_tail.y += dy / 2;
   }
   else if(std::abs(dx) == 2 and std::abs(dy) == 2)
   {
      ar_tail.x += dx / 2;
      ar_tail.y += dy / 2;
   }
   else
   {
      assert(false);
   }
   return true;
}
bool adjustTails(std::array<Pos, 10>& ar_rope)
{
   for(int i{}; i + 1 < ar_rope.size(); ++i)
      if(not adjustTail(ar_rope[i], ar_rope[i + 1]))
         return i != 0;
   return true;
}

}  // namespace
int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);
   char direction;
   int steps;
   for(; ifs >> direction >> steps;)
   {
      std::cout << '`' << direction << ' ' << steps << "'\n";
      if(direction == 'L')
      {
         for(int s{}; s != steps; ++s)
         {
            --rope.front().x;
            if(adjustTails(rope))
               tailPos.insert(rope.back());
         }
      }
      else if(direction == 'R')
      {
         for(int s{}; s != steps; ++s)
         {
            ++rope.front().x;
            if(adjustTails(rope))
               tailPos.insert(rope.back());
         }
      }
      else if(direction == 'U')
      {
         for(int s{}; s != steps; ++s)
         {
            ++rope.front().y;
            if(adjustTails(rope))
               tailPos.insert(rope.back());
         }
      }
      else if(direction == 'D')
      {
         for(int s{}; s != steps; ++s)
         {
            --rope.front().y;
            if(adjustTails(rope))
               tailPos.insert(rope.back());
         }
      }
      else
      {
         assert(false);
      }
   }
   std::cout << "The answer is " << tailPos.size() << std::endl;
   return EXIT_SUCCESS;
}
// 6284
