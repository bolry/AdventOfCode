#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace
{
using Part = std::vector<std::string>;
std::string makeRegExStringOfRule(
   int const ruleNr,
   std::unordered_map<int, Part> const& rules)
{
   if(ruleNr == 0)
   {
      auto r42 = makeRegExStringOfRule(42, rules);
      auto r31 = makeRegExStringOfRule(31, rules);
      return  // clang-format off
         "(?:(?:" + r42 + "){7,}(?:" + r31 + "){6})|"
         "(?:(?:" + r42 + "){6,}(?:" + r31 + "){5})|"
         "(?:(?:" + r42 + "){5,}(?:" + r31 + "){4})|"
         "(?:(?:" + r42 + "){4,}(?:" + r31 + "){3})|"
         "(?:(?:" + r42 + "){3,}(?:" + r31 + "){2})|"
         "(?:(?:" + r42 + "){2,}(?:" + r31 + "){1})";
              // clang-format on
   }
   std::string res;
   Part const& part = rules.find(ruleNr)->second;
   bool hasOrOperator{};
   for(auto const& p : part)
   {
      if(p.starts_with('"'))
      {
         res += p[1];
      }
      else if(p == "|")
      {
         assert(hasOrOperator == false);
         hasOrOperator = true;
         res.insert(0, "(?:");
         res += '|';
      }
      else
      {
         res.append(makeRegExStringOfRule(std::stoi(p), rules));
      }
   }
   if(hasOrOperator)
      res += ')';
   return res;
}
std::regex makeRegExOfRule(
   int const ruleNr,
   std::unordered_map<int, Part> const& rules)
{
   return std::regex(makeRegExStringOfRule(ruleNr, rules));
}
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   std::unordered_map<int, Part> rules;

   // read rules
   std::string line;
   while(std::getline(in, line) && !line.empty())
   {
      std::istringstream iss(line);
      int id;
      char ignoreColon;
      iss >> id >> ignoreColon;
      auto& part = rules[id];
      std::copy(
         std::istream_iterator<std::string>{iss},
         std::istream_iterator<std::string>{},
         back_inserter(part));
   }
   auto const regex = makeRegExOfRule(0, rules);
   // count valid messages
   std::cout << "number of valid messages "
             << std::count_if(
                   std::istream_iterator<std::string>{in},
                   std::istream_iterator<std::string>{},
                   [&regex](auto& str) { return std::regex_match(str, regex); })
             << std::endl;
}
