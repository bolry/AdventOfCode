#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>

using namespace std::ranges;

namespace
{
struct Group
{
   int nrOfCommonYes;
   friend std::istream& operator>>(std::istream& in, Group& group)
   {
      constexpr auto sz = 'z' - 'a' + 1;
      std::bitset<sz> groupAnswers;
      groupAnswers.set();
      std::string line;
      bool leastOneRead{};
      while(std::getline(in, line) && !line.empty())
      {
         leastOneRead = true;
         std::bitset<sz> personAnswers;
         for_each(line, [&bs = personAnswers](char ch) { bs.set(ch - 'a'); });
         groupAnswers &= personAnswers;
      }
      group.nrOfCommonYes = groupAnswers.count();
      if(!in && leastOneRead)
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
   std::cout << "Sum of counts where every group answered yes on the same "
                "questions is "
             << std::accumulate(
                   std::istream_iterator<Group>(in),
                   std::istream_iterator<Group>(),
                   0,
                   [](int a, Group const& b) { return a + b.nrOfCommonYes; })
             << ".\n"
             << std::flush;
   return EXIT_SUCCESS;
}
