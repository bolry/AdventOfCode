#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

namespace
{
void makeMove(int mv, std::vector<int>& circle)
{
   std::cout << "-- move " << mv << " --\ncups: ";
   std::ranges::copy(circle, std::ostream_iterator<int>(std::cout, " "));
   // remove three cups
   std::array<int, 3> takeout;
   auto b = std::next(cbegin(circle), 1);
   auto e = std::next(cbegin(circle), 1 + 3);
   std::copy(b, e, takeout.begin());
   std::cout << "\npickup: ";
   std::ranges::copy(takeout, std::ostream_iterator<int>(std::cout, ", "));
   circle.erase(b, e);
   // find designation cup
   auto label{circle.front() - 1};
   {
      auto [minIt, maxIt] = std::ranges::minmax_element(circle);
      if(label < *minIt)
         label = *maxIt;
   }
   for(;;)
   {
      auto iter = std::find(cbegin(circle), cend(circle), label);
      if(iter == cend(circle))
      {
         --label;
      }
      else
      {
         std::cout << "\ndestination: " << label << "\n\n";
         circle.insert(std::next(iter), cbegin(takeout), cend(takeout));
         break;
      }
   }
   // and that's a rotate
   std::ranges::rotate(circle, std::next(begin(circle)));
}
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   std::vector<int> v;
   std::transform(
      std::istreambuf_iterator<char>{in},
      {},
      std::back_inserter(v),
      [](char c) { return c - '0'; });
   for(int i = 0; i < 100; ++i)
      makeMove(i + 1, v);
   // move label '1' first
   std::ranges::rotate(v, std::ranges::find(v, 1));
   std::copy(std::next(cbegin(v)), cend(v), std::ostream_iterator<int>(std::cout,""));
   return 0;
}
