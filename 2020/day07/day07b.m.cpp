#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

namespace
{
using Content = std::unordered_map<std::string, unsigned>;
using Rules   = std::unordered_map<std::string, Content>;

Rules rules;

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
   Content content;
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
      iss >> word;
      rule.content.clear();
      if(word == "no")
         return in;
      for(;; iss >> word)
      {
         auto const count = std::stoul(word);
         iss >> bt >> word;
         rule.content[bt.bagType] = static_cast<unsigned>(count);
         if(word.ends_with('.'))
            return in;
      }
   }
};

std::uintmax_t countBagsForColor(Rules const& rs, std::string const& color)
{
   auto const& content = rs.find(color)->second;
   std::uintmax_t bagCnt{};
   for(auto const& bag : content)
      bagCnt += bag.second + bag.second * countBagsForColor(rs, bag.first);
   return bagCnt;
}

}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   for(auto it   = std::istream_iterator<Rule>(in),
            last = std::istream_iterator<Rule>();
       it != last;
       ++it)
      rules.emplace(it->bagType, it->content);
   std::cout << countBagsForColor(rules, "shiny gold") << std::endl;
   return EXIT_SUCCESS;
}
