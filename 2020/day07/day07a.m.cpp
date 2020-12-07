#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace
{
using namespace std::ranges;
using namespace std::literals;

struct BagType
{
   std::string bagType;
   friend std::istream& operator>>(std::istream& in, BagType& type)
   {
      std::string color;
      in >> type.bagType >> color;
      type.bagType += ' ' + std::move(color);
      return in;
   }
};

struct Rule
{
   std::string bagType;
   std::unordered_map<std::string, int> contains;
   friend std::istream& operator>>(std::istream& in, Rule& rule)
   {
      std::string line;
      if(!std::getline(in, line))
         return in;
      std::istringstream iss(line);
      std::string word;
      BagType bt;
      iss >> bt >> word >> word;
      rule.bagType = std::move(bt.bagType);
      assert(word == "contain"sv);
      iss >> word;
      rule.contains.clear();
      if(word == "no"sv)
         return in;
      for(;; iss >> word)
      {
         int count = std::stoi(word);
         iss >> bt >> word;
         rule.contains[bt.bagType] = count;
         if(word.ends_with('.'))
            return in;
      }
   }
};

void countCanCarrayColor(
   std::vector<Rule> const& rules,
   std::string const& color,
   std::unordered_set<std::string>& canCarray)
{
   std::vector<std::string> newFindings;
   for(auto const& rule : rules)
      if(rule.contains.contains(color) && canCarray.insert(rule.bagType).second)
         newFindings.push_back(rule.bagType);
   for(auto const& newColor : newFindings)
      countCanCarrayColor(rules, newColor, canCarray);
}


}  // namespace

int main()
{
   using namespace std::ranges;
   std::ifstream in("../input.txt");
   std::vector<Rule> rules;
   rules.reserve(594);
   copy(
      std::istream_iterator<Rule>(in),
      std::istream_iterator<Rule>(),
      back_inserter(rules));
   std::unordered_set<std::string> canCarray;
   countCanCarrayColor(rules, "shiny gold"s, canCarray);
   //copy(canCarray, std::ostream_iterator<std::string>(std::cout, "\n"));
   std::cout << size(canCarray) << std::endl;
   return EXIT_SUCCESS;
}
