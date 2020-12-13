//#define _GLIBCXX_DEBUG
//#define _GLIBCXX_DEBUG_PEDANTIC

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>

using namespace std::ranges;

namespace
{
struct CtypeExtraSpaces : std::ctype<char>
{
   static auto makeTable()
   {
      static std::vector v(classic_table(), classic_table() + table_size);
      v[','] |= space;
      v['x'] |= space;
      return v.data();
   }
   explicit CtypeExtraSpaces(size_t refs = 0U) : ctype{makeTable(), false, refs}
   {
   }
};

using Timestamp = std::uintmax_t;
using BusId     = std::uintmax_t;
}  // namespace

int main()
{
#if 1
   std::ifstream in("../input.txt");
#else
   std::istringstream in(R"(939
7,13,x,x,59,x,31,19
)");
#endif
   in.imbue(std::locale{std::cin.getloc(), new CtypeExtraSpaces});
   Timestamp startTs = std::invoke(
      [](std::istream& i) {
         Timestamp res;
         i >> res;
         return res;
      },
      in);
   std::vector<Timestamp> busIDs(
      std::istream_iterator<BusId>{in}, std::istream_iterator<BusId>{});
   auto nextDeparture = busIDs;
   std::cout << "Start at " << startTs << "\nBus id's: ";
   copy(busIDs, std::ostream_iterator<BusId>(std::cout, " "));
   std::cout << "\nNext departures: ";
   transform(busIDs, begin(nextDeparture), [s = startTs](auto id) {
      return (s + (id - 1)) / id * id;
   });
   copy(nextDeparture, std::ostream_iterator<BusId>(std::cout, " "));
   auto nextBusIter = min_element(nextDeparture);
   auto busIdOffset = distance(begin(nextDeparture), nextBusIter);
   std::cout << "\nTake bus " << busIDs[busIdOffset] << " at time "
             << *nextBusIter << " thus waiting " << *nextBusIter - startTs
             << "\nAnswer " << (*nextBusIter - startTs) * busIDs[busIdOffset]
             << '\n'
             << std::flush;
}
