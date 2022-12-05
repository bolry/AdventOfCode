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

int overlap(Assignment left, Assignment right)
{
   if(left.last >= right.first and left.first <= right.last)
      return 1;
   if(right.last >= left.first and right.first <= left.last)
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
      cnt += overlap(left, right);
   }
   std::cout << cnt << '\n';
   return EXIT_SUCCESS;
}
