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
using Set = std::unordered_set<Pos>;
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
Pos head{};
Pos tail{};
Set tailPos{tail};
void adjustTail() noexcept
{
   int const dx = head.x - tail.x;
   int const dy = head.y - tail.y;
   if(std::abs(dx) <= 1 and std::abs(dy) <= 1)
      return;
   else if(dy == 0)
   {
      // T.H -> .TH
      // H.T -> HT.
      tail.x += dx / 2;
   }
   else if(dx == 0)
   {
      tail.y += dy / 2;
   }
   else if(std::abs(dy) == 1)
   {
      tail.x += dx / 2;
      tail.y += dy;
   }
   else if(std::abs(dx) == 1)
   {
      tail.x += dx;
      tail.y += dy / 2;
   }
   else
   {
      assert(false);
   }
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
            --head.x;
            adjustTail();
            tailPos.insert(tail);
         }
      }
      else if(direction == 'R')
      {
         for(int s{}; s != steps; ++s)
         {
            ++head.x;
            adjustTail();
            tailPos.insert(tail);
         }
      }
      else if(direction == 'U')
      {
         for(int s{}; s != steps; ++s)
         {
            ++head.y;
            adjustTail();
            tailPos.insert(tail);
         }
      }
      else if(direction == 'D')
      {
         for(int s{}; s != steps; ++s)
         {
            --head.y;
            adjustTail();
            tailPos.insert(tail);
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
