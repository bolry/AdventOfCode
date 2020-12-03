#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

namespace
{
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   std::vector<std::string> map;
   map.reserve(323);
   std::copy(
      std::istream_iterator<std::string>(in),
      std::istream_iterator<std::string>(),
      std::back_inserter(map));
   int treeCnt{};
   int col{};
   for(int rowId = 0; rowId < ssize(map); ++rowId)
   {
      if(col >= ssize(map[rowId]))
      {
         col %= ssize(map[rowId]);
      }
      if(map[rowId][col] == '#')
      {
         ++treeCnt;
      }
      col += 3;
   }
   std::cout << "Found " << treeCnt << " trees\n" << std::flush;
   return EXIT_SUCCESS;
}
