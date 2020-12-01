#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
   std::ifstream in("../input.txt");
   std::vector<int> vints;
   vints.reserve(200);
   std::copy(
      std::istream_iterator<int>(in),
      std::istream_iterator<int>(),
      std::back_inserter(vints));
   in.close();
   while(!vints.empty())
   {
      auto& v   = vints.front();
      auto iter = std::find(next(cbegin(vints)), cend(vints), 2020 - v);
      if(iter == cend(vints))
      {
         v = vints.back();
         vints.pop_back();
      }
      else
      {
         std::cout << "Answer is " << v * *iter << std::endl;
         return EXIT_SUCCESS;
      }
   }
   return EXIT_FAILURE;
}
