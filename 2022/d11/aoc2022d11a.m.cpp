#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace
{
using Int = std::intmax_t;
struct Monkey
{
   Int id;
   std::vector<Int> items;
   std::function<Int(Int)> operation;
   Int divBy;
   Int trueMonkey;
   Int falseMonkey;
   std::size_t stats{};
};
std::istream& operator>>(std::istream& in, Monkey& r_monkey)
{
   std::string ign;
   in >> ign >> r_monkey.id >> ign >> ign >> ign;
   if(not in)
      return in;
   assert(ign == "items:");
   r_monkey.items.clear();
   Int item;
   in >> item;
   assert(in);
   r_monkey.items.push_back(item);
   for(;;)
   {
      char ch{};
      in >> ch;
      assert(in);
      if(ch == ',')
      {
         in >> item;
         assert(in);
         r_monkey.items.push_back(item);
      }
      else
      {
         assert(ch == 'O');
         break;
      }
   }
   in >> ign >> ign >> ign >> ign;
   assert(in && ign == "old");
   char sign{};
   in >> sign;
   Int k;
   if(in >> k)
      if(sign == '+')
         r_monkey.operation = [k](Int old) { return old + k; };
      else if(sign == '*')
         r_monkey.operation = [k](Int old) { return old * k; };
      else
         assert(false);
   else
   {
      in.clear();
      in >> ign;
      assert(in && ign == "old");
      if(sign == '+')
         r_monkey.operation = [](Int old) { return old + old; };
      else if(sign == '*')
         r_monkey.operation = [](Int old) { return old * old; };
      else
         assert(false);
   }
   in >> ign >> ign >> ign >> r_monkey.divBy;
   in >> ign >> ign >> ign >> ign >> ign >> r_monkey.trueMonkey;
   in >> ign >> ign >> ign >> ign >> ign >> r_monkey.falseMonkey;
   assert(in);
   return in;
}
}  // namespace
int main()
{
   std::vector<Monkey> monkeys;
   monkeys.reserve(8);
   {
      std::ifstream ifs{"../input.txt"};
      assert(ifs);
      using In = std::istream_iterator<Monkey>;
      monkeys.assign(In{ifs}, {});
   }
   for(std::size_t i{}; i != monkeys.size(); ++i)
      assert(monkeys[i].id == i);
   constexpr int maxRounds{20};
   for(int round{}; round != maxRounds; ++round)
      for(auto& monkey : monkeys)
      {
         for(auto item : monkey.items)  // copy
         {
            item = monkey.operation(item);
            item /= 3;
            auto newId = item % monkey.divBy == 0 ? monkey.trueMonkey
                                                  : monkey.falseMonkey;
            monkeys[newId].items.push_back(item);
         }
         monkey.stats += monkey.items.size();
         monkey.items.clear();  // assuming no monkey throws to himself
      }
   auto _2ndPlace = next(begin(monkeys));
   namespace r4s  = std::ranges;
   r4s::nth_element(monkeys, _2ndPlace, [](auto const& a, auto const& b) {
      return b.stats < a.stats;
   });
   std::cout << "Monkey business after " << maxRounds << " rounds is "
             << monkeys[0].stats * monkeys[1].stats << std::endl;
   // 119715
   return EXIT_SUCCESS;
}
