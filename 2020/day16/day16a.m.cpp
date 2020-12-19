#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
struct CtypeExtraSpaces : std::ctype<char>
{
   static auto makeTable()
   {
      static std::vector v(classic_table(), classic_table() + table_size);
      v[','] |= space;
      return v.data();
   }
   explicit CtypeExtraSpaces(size_t refs = 0U) : ctype{makeTable(), false, refs}
   {
   }
};

struct Rng
{
   int low;
   int hi;
   friend std::istream& operator>>(std::istream& in, Rng& rng)
   {
      in >> rng.low >> rng.hi;
      rng.hi *= -1;
      return in;
   }
};

int invalidValue(std::vector<Rng> const& rngs, int i)
{
   for(auto const& rng : rngs)
      if(rng.low <= i && i <= rng.hi)
         return 0;
   return i;
}
}  // namespace

int main()
{
   auto in =
#if 0
      std::istringstream(R"(class: 1-3 or 5-7
row: 6-11 or 33-44
seat: 13-40 or 45-50

your ticket:
7,1,14

nearby tickets:
7,3,47
40,4,50
55,2,20
38,6,12
)");
   std::ifstream{"/dev/null"};
#else
      std::ifstream("../input.txt");
#endif
      std::string line;
   std::vector<Rng> rngs;
   // read ranges
   while(std::getline(in, line) && !line.empty())
   {
      std::istringstream iss(line);
      std::getline(iss, line, ':');
      Rng rng;
      iss >> rng;
      rngs.push_back(rng);
      iss >> line >> rng;
      rngs.push_back(rng);
   }
   // read pass your ticket
   while(std::getline(in, line) && !line.empty())
   {
      // ignore
   }
   // read nearby tickets
   std::getline(in, line);  // "nearby tickets:"
   in.imbue(std::locale{in.getloc(), new CtypeExtraSpaces});
   std::cout << std::accumulate(
      std::istream_iterator<int>{in},
      std::istream_iterator<int>{},
      0,
      [&rngs](int a, int b) { return a + invalidValue(rngs, b); });
   return EXIT_SUCCESS;
}
