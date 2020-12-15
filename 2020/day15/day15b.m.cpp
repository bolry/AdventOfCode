#include <iostream>
#include <unordered_map>

int main()
{
   constexpr auto lastTurn = 30'000'000;
   std::unordered_map<int, int> v{
      {5, 1}, {1, 2}, {9, 3}, {18, 4}, {13, 5}, {8, 6}};
   int nextSpoken = 0;
   int lastSpoken{};
   for(int turn = ssize(v); turn < lastTurn;)
   {
      ++turn;
      lastSpoken = nextSpoken;
      // std::cout << "Turn " << turn  << ": " << lastSpoken << '\n';
      auto& offset = v[nextSpoken];
      if(offset == 0) [[unlikely]]
      {
         nextSpoken = 0;
      }
      else
      {
         nextSpoken = turn - offset;
      }
      offset = turn;
   }
   std::cout << "Last spoken is " << lastSpoken << std::endl;
}
