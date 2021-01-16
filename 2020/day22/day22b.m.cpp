#include <algorithm>
#include <cassert>
#include <cstdint>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

using namespace std::string_view_literals;

namespace
{
using Hand = std::deque<int>;

Hand readHand(std::istream& in)
{
   Hand hand;
   std::string line;
   std::getline(in, line);
   assert(line.starts_with("Player"sv));
   while(std::getline(in, line) && !line.empty())
      hand.push_back(std::stoi(line));
   return hand;
}

void printHand(int id, Hand const& hand)
{
   std::cout << "Player " << id << "'s deck: ";
   std::ranges::copy(hand, std::ostream_iterator<int>(std::cout, ", "));
   std::cout << '\n';
}

void preTrace(int round, Hand const& hand1, Hand const& hand2)
{
   std::cout << "-- Round " << round << " --\n";
   printHand(1, hand1);
   printHand(2, hand2);
   std::cout << "Player 1 plays: " << hand1.front() << '\n';
   std::cout << "Player 2 plays: " << hand2.front() << '\n';
}

void postTrace(int winner)
{
   std::cout << "Player " << winner << " wins the round!\n\n";
}

void postGameResult(Hand const& hand1, Hand const& hand2)
{
   std::cout << "\n== Post-game results ==\n";
   printHand(1, hand1);
   printHand(2, hand2);
}

auto calcScore(Hand const& hand)
{
   std::vector<int> v(hand.size(), 0);
   std::iota(v.rbegin(), v.rend(), 1);
   return std::inner_product(
      hand.begin(), hand.end(), v.begin(), 0);
}

}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   Hand player1 = readHand(in);
   Hand player2 = readHand(in);
   for(int round = 1; !player1.empty() && !player2.empty(); ++round)
   {
      preTrace(round, player1, player2);
      auto card1 = player1.front();
      auto card2 = player2.front();
      assert(card1 != card2);
      player1.pop_front();
      player2.pop_front();
      if(card1 > card2)
      {
         postTrace(1);
         player1.push_back(card1);
         player1.push_back(card2);
      }
      else
      {
         postTrace(2);
         player2.push_back(card2);
         player2.push_back(card1);
      }
   }
   postGameResult(player1, player2);
   auto score = player2.empty() ? calcScore(player1) : calcScore(player2);
   std::cout << "\nScore " << score << std::endl;
}
