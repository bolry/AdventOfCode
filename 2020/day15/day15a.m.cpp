#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace
{
void printTurns(std::vector<int> const& v)
{
   for(int i = 0, e = ssize(v); i < e; ++i)
      std::cout << "Turn " << i + 1 << ": " << v[i] << '\n';
}
}  // namespace

int main()
{
   constexpr auto lastTurn = 2020;
   std::vector v{5, 1, 9, 18, 13, 8, 0};
   v.reserve(lastTurn);
   for(int i = ssize(v); i < lastTurn; ++i)
      if(auto x = rbegin(v), it = find(++x, rend(v), v.back()); it == rend(v))
         v.push_back(0);
      else
         v.push_back(distance(rbegin(v), it));
   // printTurns(v);
   std::cout << "Last spoken is " << v.back() << std::endl;
}
