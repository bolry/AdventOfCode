#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>

namespace
{
struct Box
{
   int l;
   int w;
   int h;
   friend std::istream& operator>>(std::istream& in, Box& box)
   {
      char x;
      in >> box.l >> x >> box.w >> x >> box.h;
      return in;
   }
};

int ribbonToWrap(Box const& box)
{
   std::array<int, 3> sides{box.l, box.w, box.h};
   std::ranges::sort(sides);
   return std::inner_product(
      cbegin(sides),
      std::prev(cend(sides)),
      cbegin(sides),
      0,
      std::plus<>(),
      std::plus<>());
}

int ribbonForBow(Box const& box)
{
   return box.l * box.w * box.h;
}

}  // namespace
int main()
{
   std::ifstream in("../input.txt");
   int const sqFeetWrappingPaperNeeded = std::accumulate(
      std::istream_iterator<Box>(in),
      std::istream_iterator<Box>(),
      0,
      [](int a, Box const& b) {
         return a + ribbonToWrap(b) + ribbonForBow(b);
      });
   std::cout << "Total square feet of wrapping paper to order is "
             << sqFeetWrappingPaperNeeded << std::endl;
}
