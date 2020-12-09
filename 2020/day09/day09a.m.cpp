#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std::literals;
using namespace std::ranges;

namespace
{
constexpr int preambleSz{25};

bool isSumOfTwo(std::vector<std::uintmax_t> const& vec, std::uintmax_t const v)
{
   for(int i = 0, e = ssize(vec) - 1; i < e; ++i)
   {
      auto it = find(std::next(cbegin(vec), i + 1), cend(vec), v - vec[i]);
      if(it != cend(vec) && *it != vec[i])
         return true;
   }
   return false;
}

}  // namespace

int main()
{
   std::ifstream in("../input.txt"s);
   std::vector<std::uintmax_t> values;
   for(auto f = std::istream_iterator<std::uintmax_t>{in},
            l = std::istream_iterator<std::uintmax_t>{};
       f != l;
       ++f)
   {
      auto const v = *f;
      if(ssize(values) != preambleSz)
      {
         values.push_back(v);
         continue;
      }

      if(!isSumOfTwo(values, v))
      {
         std::cout << "Does not fit " << v << '\n';
         return EXIT_FAILURE;
      }
      values.push_back(v);
      while(values.size() > preambleSz)
         values.erase(cbegin(values));
   }
   std::cout << std::flush;
   return EXIT_SUCCESS;
}
