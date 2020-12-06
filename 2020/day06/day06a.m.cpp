#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <string>

using namespace std::ranges;

namespace
{
struct Group
{
   int nrOfYes;
   friend std::istream& operator>>(std::istream& in, Group& group)
   {
      std::array<bool, std::numeric_limits<char>::max()> answers{};
      std::string line;
      while(std::getline(in, line) && !line.empty())
      {
         for_each(line, [&answers](char ch) { answers[ch] = true; });
      }
      group.nrOfYes = count(answers, true);
      if(!in && group.nrOfYes != 0)
      {
         in.clear();
      }
      return in;
   }
};
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   std::cout << "Sum of counts of groups with at least one yes each is "
             << accumulate(
                   std::istream_iterator<Group>(in),
                   std::istream_iterator<Group>(),
                   0,
                   [](int a, Group const& b) { return a + b.nrOfYes; })
             << " groups\n"
             << std::flush;
   return EXIT_SUCCESS;
}
