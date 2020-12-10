#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std::literals;
using namespace std::ranges;

namespace
{
constexpr std::array kTranslate{1, 1, 2, 4, 7};
}

int main()
{
   std::ifstream in("../input.txt"s);
   using inIter = std::istream_iterator<int>;
   std::vector vec(inIter{in}, inIter{});
   sort(vec);
   vec.push_back(vec.back() + 3);
   adjacent_difference(cbegin(vec), cend(vec), begin(vec));
   std::vector<std::uint_fast8_t> ones;
   for(auto b{cbegin(vec)}, i{b}, e{cend(vec)}; (i = find(i, e, 3)) != e;
       b = i = find(i, e, 1))
      ones.push_back(kTranslate[distance(b, i)]);
   std::cout << reduce(
                   cbegin(ones),
                   cend(ones),
                   std::uintmax_t{1},
                   std::multiplies<>{})
             << std::endl;
   return EXIT_SUCCESS;
}
