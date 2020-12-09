#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std::literals;
using namespace std::ranges;

namespace
{
constexpr int searchSum{21806024};
}  // namespace

int main()
{
   std::ifstream in("../input.txt"s);
   std::vector<std::uintmax_t> values;
   copy(
      std::istream_iterator<std::uintmax_t>{in},
      std::istream_iterator<std::uintmax_t>{},
      std::back_inserter(values));
   std::vector<std::uintmax_t> sums;
   sums.reserve(size(values));

   for(int i = 0, e = ssize(values); i < e; ++i)
   {
      sums.clear();
      std::partial_sum(
         std::next(cbegin(values), i), cend(values), std::back_inserter(sums));
      auto it = find(sums, searchSum);
      if(it != end(sums) && std::distance(begin(sums), it) >= 2)
      {
         int offset            = 1 + std::distance(begin(sums), it);
         auto const [min, max] = minmax_element(
            std::next(cbegin(values), i),
            std::next(cbegin(values), i + offset));
         std::cout << "Found " << *min << " and " << *max << " with SUM "
                   << *min + *max << std::endl;
         return EXIT_SUCCESS;
      }
   }
   std::cout << "Sorry" << std::flush;
   return EXIT_FAILURE;
}
