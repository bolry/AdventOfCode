#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

namespace
{
constexpr auto nullPair = std::make_pair(0, 0);

std::pair<int, int> findPair(std::vector<int>& vints, int goalSum)
{
   while(!vints.empty())
   {
      auto& v = vints.front();
      auto it = std::find(next(cbegin(vints)), cend(vints), goalSum - v);
      if(it != cend(vints))
      {
         return {v, *it};
      }
      v = vints.back();
      vints.pop_back();
   }
   return nullPair;
}
}  // namespace
int main()
{
   std::ifstream in("../input.txt");
   std::vector<int> vints;
   vints.reserve(200);
   std::copy(
      std::istream_iterator<int>(in),
      std::istream_iterator<int>(),
      back_inserter(vints));
   in.close();
   decltype(vints) cvints;
   cvints.reserve(199);
   while(!vints.empty())
   {
      auto& v = vints.front();
      cvints.assign(next(cbegin(vints)), cend(vints));
      auto const p = findPair(cvints, 2020 - v);
      if(p != nullPair)
      {
         std::cout << "Answer is " << v * p.first * p.second << std::endl;
         return EXIT_SUCCESS;
      }
      v = vints.back();
      vints.pop_back();
   }
   return EXIT_FAILURE;
}
