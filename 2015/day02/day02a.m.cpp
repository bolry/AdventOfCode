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

int calculatingRequiredWrappingPaper(Box const& box)
{
   std::array<int, 3> const sides{
      2 * box.l * box.w, 2 * box.w * box.h, 2 * box.h * box.l};
   return std::accumulate(cbegin(sides), cend(sides), 0) +
          *std::ranges::min_element(sides) / 2;
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
         return a + calculatingRequiredWrappingPaper(b);
      });
   std::cout << "Total square feet of wrapping paper to order is "
             << sqFeetWrappingPaperNeeded << std::endl;
}
