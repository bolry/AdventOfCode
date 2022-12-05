#include <algorithm>
#include <cassert>
#include <charconv>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>

int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);
   std::string line;
   int maxCalories{};
   int calories{};
   while(std::getline(ifs, line)) [[likely]]
   {
      if(line.empty()) [[unlikely]]
      {
         maxCalories = std::max(maxCalories, calories);
         calories    = 0;
      }
      else
      {
         int cal;
         auto [_, ec] = std::from_chars(
            line.data(), line.data() + line.size(), cal);
         assert(ec == std::errc{});
         calories += cal;
      }
   }
   maxCalories = std::max(maxCalories, calories);
   std::cout << maxCalories << '\n';
   return EXIT_SUCCESS;
}
