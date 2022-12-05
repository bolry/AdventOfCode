#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace
{
struct Assignment
{
   int first;
   int last;

   friend std::istream& operator>>(std::istream& in, Assignment& assignment)
   {
      in >> assignment.first >> assignment.last;
      assignment.last = -assignment.last;
      return in;
   }
};

int fullyContains(Assignment left, Assignment right) noexcept
{
   if(left.first <= right.first and left.last >= right.last)
      return 1;
   if(right.first <= left.first and right.last >= left.last)
      return 1;
   return 0;
}

}  // namespace

int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);
   int cnt{};
   char ignoreComma;
   Assignment left{};
   Assignment right{};
   while(ifs >> left >> ignoreComma >> right)
   {
      cnt += fullyContains(left, right);
   }
   std::cout << cnt << '\n';
   return EXIT_SUCCESS;
}
