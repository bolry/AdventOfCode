#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

namespace
{
std::array<signed char, std::numeric_limits<unsigned char>::max()>
   translateDirection{};
}
int main()
{
   translateDirection['('] = 1;
   translateDirection[')'] = -1;
   std::ifstream in("../input.txt");
   std::vector<int> ints;
   ints.reserve(7000);
   std::transform(
      std::istream_iterator<unsigned char>(in),
      std::istream_iterator<unsigned char>(),
      back_inserter(ints),
      [](auto a) -> int { return translateDirection[a]; });
   std::partial_sum(cbegin(ints), cend(ints), begin(ints));
   std::cout << "Santa in basement at position "
             << 1 + std::distance(
                       cbegin(ints), std::ranges::find(as_const(ints), -1))
             << std::endl;
}
