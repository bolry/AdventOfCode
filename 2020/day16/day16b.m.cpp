#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std::ranges;

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

struct Field
{
   std::string name;
   std::array<Rng, 2> rngs;
   friend std::istream& operator>>(std::istream& in, Field& field)
   {
      if(std::getline(in, field.name, ':'))
      {
         std::string ignoreOrWord;
         in >> field.rngs[0] >> ignoreOrWord >> field.rngs[1];
      }
      return in;
   }
};

using Ticket = std::vector<int>;

Ticket readTicket(std::istream& in)
{
   std::string line;
   std::getline(in, line);
   std::istringstream iss(line);
   iss.imbue(std::locale{iss.getloc(), new CtypeExtraSpaces});
   Ticket ticket(std::istream_iterator<int>{iss}, std::istream_iterator<int>{});
   return ticket;
}

bool isValidRng(std::array<Rng, 2> const& rngs, int i)
{
   for(auto const& rng : rngs)
      if(rng.low <= i && i <= rng.hi)
         return true;
   return false;
}

bool isValidTicket(std::vector<Field> const& fields, Ticket const& ticket)
{
   for(int i : ticket)  // all i's must be valid somewhere
   {
      for(auto const& field : fields)
         if(isValidRng(field.rngs, i))
            goto nextI;
      return false;
   nextI:;
   }
   return true;
}
}  // namespace

bool allTicketsValid(
   std::vector<Field> const& fields,
   std::vector<Ticket> const& tickets)
{
   for(auto const& ticket : tickets)
   {
      assert(size(ticket) == size(fields));
      auto sz = size(fields);
      for(decltype(sz) idx{}; idx < sz; ++idx)
      {
         if(!isValidRng(fields[idx].rngs, ticket[idx]))
            return false;
      }
   }
   return true;
}
int main()
{
   auto in =
#if 0
      std::istringstream(R"(class: 0-1 or 4-19
row: 0-5 or 8-19
seat: 0-13 or 16-19

your ticket:
11,12,13

nearby tickets:
3,9,18
15,1,5
5,14,9
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
   // read fields
   std::vector<Field> fields;
   while(std::getline(in, line) && !line.empty())
   {
      std::istringstream iss(line);
      Field field;
      if(iss >> field)
         fields.push_back(std::move(field));
      else
         assert(false);
   }
   // read pass your ticket
   std::getline(in, line);  // "your ticket:"
   Ticket yourTicket = readTicket(in);
   std::getline(in, line);  // empty line
   // identify valid nearby tickets
   std::getline(in, line);  // "nearby tickets:"
   std::vector<Ticket> validNearTickets;
   for(;;)
   {
      Ticket ticket = readTicket(in);
      if(ticket.empty())
         break;
      if(isValidTicket(fields, ticket))
         validNearTickets.push_back(std::move(ticket));
   }
   // find right order of fields
   while(!allTicketsValid(fields, validNearTickets))
   {
      next_permutation(fields, [](Field const& a, Field const& b) {
         return a.name < b.name;
      });
   }
   for(int i = 0; i < ssize(fields); ++i)
   {
      std::cout << i << ": " << fields[i].name << '\n';
   }
   return EXIT_SUCCESS;
}
