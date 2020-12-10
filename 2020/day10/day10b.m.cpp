#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std::literals;
using namespace std::ranges;

int main()
{
   std::ifstream in("../input.txt"s);
   std::vector<int> vec(
      std::istream_iterator<int>{in}, std::istream_iterator<int>{});
   sort(vec);
   vec.push_back(vec.back() + 3);
   adjacent_difference(cbegin(vec), cend(vec), begin(vec));
   copy(vec, std::ostream_iterator<int>(std::cout, " "));
   std::cout << std::flush;
   return EXIT_SUCCESS;
}
