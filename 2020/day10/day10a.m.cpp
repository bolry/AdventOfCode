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
   auto const ones   = count(vec, 1);
   auto const threes = count(vec, 3);
   std::cout << "1's = " << ones << " 3's = " << threes
             << " multiply = " << ones * threes << std::flush;
   return EXIT_SUCCESS;
}
