#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <calc2.h>

int main()
{
   std::vector<pkg::Result> results;
   std::ifstream in("../input.txt");
   std::string line;
   while(std::getline(in, line))
   {
      std::istringstream iss(line);
      pkg::Calc2 calc{iss};
      auto t = calc.eval();
      if(t.kind != pkg::kQuit)
         results.push_back(t.value);
   }
   std::cout << "Sum is "
             << std::accumulate(cbegin(results), cend(results), pkg::Result{})
             << std::endl;
}
