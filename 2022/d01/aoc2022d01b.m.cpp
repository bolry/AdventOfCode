#include <algorithm>
#include <cassert>
#include <charconv>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <system_error>
#include <vector>

int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);
   std::string line;
   std::vector<int> carrying;
   carrying.reserve(3000);
   int calories{};
   while(std::getline(ifs, line)) [[likely]]
   {
      if(line.empty()) [[unlikely]]
      {
         carrying.push_back(calories);
         calories = 0;
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
   carrying.push_back(calories);
   auto b = carrying.begin();
   std::ranges::nth_element(carrying, next(b, 2), std::greater<>());
   std::cout << std::accumulate(b, next(b, 3), int{}) << '\n';
}
