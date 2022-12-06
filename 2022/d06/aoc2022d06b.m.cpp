#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);
   using In = std::istreambuf_iterator<char>;
   std::string stream(In{ifs}, {});
   int offset{};
   for(;; ++offset)
   {
      std::string check = stream.substr(offset, 14);
      namespace r4s     = std::ranges;
      r4s::sort(check);
      if(r4s::adjacent_find(check) == check.end()) [[unlikely]]
         break;
   }
   std::cout << offset + 14 << '\n';
   return EXIT_SUCCESS;
}
