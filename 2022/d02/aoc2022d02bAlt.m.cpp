#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);
   int sum{};
   for(std::string line; std::getline(ifs, line);)
   {
      int s;
      // clang-format off
      if(line == "A X") s = 3;
      else if(line == "A Y") s = 4;
      else if(line == "A Z") s = 8;
      else if(line == "B X") s = 1;
      else if(line == "B Y") s = 5;
      else if(line == "B Z") s = 9;
      else if(line == "C X") s = 2;
      else if(line == "C Y") s = 6;
      else /*if (line == "C Z")*/ s = 7;
      // clang-format on
      sum += s;
   }
   std::cout << "\nTotal score " << sum << '\n';

   return EXIT_SUCCESS;
}
