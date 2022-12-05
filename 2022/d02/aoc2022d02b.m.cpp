#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace
{
enum Shape
{
   Rock = 1,
   Paper,
   Scissors,
};

constexpr Shape toFig(char ch) noexcept
{
   return Shape((ch - 'A') + 1);
}

constexpr int myScore(char wantOutcome, char otherShape) noexcept
{
   Shape myFig;
   Shape otherFig = toFig(otherShape);
   if(wantOutcome == 'X')  // lose
   {
      if(otherFig == Rock)
         myFig = Scissors;
      else if(otherFig == Paper)
         myFig = Rock;
      else /*if (otherFig == Scissors)*/
         myFig = Paper;
   }
   else if(wantOutcome == 'Y')  // draw
   {
      myFig = otherFig;
   }
   else /*if (wantOutcome == 'Z')*/  // win
   {
      if(otherFig == Rock)
         myFig = Paper;
      else if(otherFig == Paper)
         myFig = Scissors;
      else /*if (otherFig == Scissors)*/
         myFig = Rock;
   }
   // tie
   if(myFig == otherFig)
      return 3 + myFig;
   // I win
   else if(
      (myFig == Rock and otherFig == Scissors) or
      (myFig == Scissors and otherFig == Paper) or
      (myFig == Paper and otherFig == Rock))
      return 6 + myFig;
   // I lose
   else
      return myFig;
}
}  // namespace

int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);

   int sum{};
   for(std::string line; std::getline(ifs, line);)
   {
      assert(line.size() == 3);
      int s = myScore(line[2], line[0]);
      std::cout << '`' << line << "' score: " << s << '\n';
      sum += s;
   }
   std::cout << "\nTotal score " << sum << '\n';

   return EXIT_SUCCESS;
}
