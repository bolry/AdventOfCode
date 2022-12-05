#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stack>
#include <string>
#include <utility>
#include <vector>

namespace
{

constexpr bool isupper(char ch) noexcept
{
   return std::isupper(static_cast<unsigned char>(ch));
}

constexpr int kStacks{9};  // known from my input data

using Stack  = std::stack<char, std::string>;
using Stacks = std::vector<Stack>;

Stacks getStacks(std::istream& in)
{
   std::array<std::string, kStacks> strs;
   std::string line;
   while(std::getline(in, line))
   {
      if(line[1] == '1')
         break;
      int idx{};
      for(int i{1}; i < line.size(); i += 4)
      {
         char mark = line[i];
         if(isupper(mark))
            strs[idx].push_back(mark);
         ++idx;
      }
   }
   constexpr auto unlimited = std::numeric_limits<std::streamsize>::max();
   in.ignore(unlimited, '\n');
   namespace r4s = std::ranges;
   r4s::for_each(strs, r4s::reverse);
   Stacks stacks;
   for(auto& str : strs)
      stacks.emplace_back(std::move(str));
   return stacks;
}
}  // namespace

int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);
   auto stacks = getStacks(ifs);
   std::string ign;
   for(int moves, from, to; ifs >> ign >> moves >> ign >> from >> ign >> to;)
   {
      for(auto const& stack : stacks)
         std::cout << stack.top();
      std::cout << '\n';
      std::cout << moves << ' ' << from << ' ' << to << '\n';
      auto& stackFrom = stacks[from - 1];
      auto& stackTo   = stacks[to - 1];
      for(int mv{}; mv != moves; ++mv)
      {
         stackTo.push(stackFrom.top());
         stackFrom.pop();
      }
   }
   for(auto const& stack : stacks)
      std::cout << stack.top();
   return EXIT_SUCCESS;
}
