#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <locale>
#include <numeric>
#include <sstream>

using namespace std::ranges;

namespace
{
struct WsComma : std::ctype<char>
{
   static auto makeTable()
   {
      static std::vector v(classic_table(), classic_table() + table_size);
      v[','] |= space;
      return v.data();
   }

   explicit WsComma(size_t refs = 0U) : ctype{makeTable(), false, refs} {}
};

using Timestamp = std::uintmax_t;
struct BusInfo
{
   std::uint_fast16_t id{};
   std::uint_fast8_t offset{};
};
}  // namespace

int main()
{
#if 1
   std::ifstream in("../input.txt");
#else
   std::istringstream in(
      "xxx\n"
      // clang-format off
//"7,13"  // 77
//"7,13,x,x,59"  // 350
//"7,13,x,x,59,x,31"  // 70147
//"7,13,x,x,59,x,31,19"  // 1068781
//"17,x,13"  // Start 0 Step 17 LCM 221 Tries 7 G 102
//"17,x,13,19"  // Start 102 Step 221 LCM 4199 Tries 16 G 3417
//"67,7"  // Start 0 Step 67 LCM 469 Tries 6 G 335
//"67,7,59"  // Start 335 Step 469 LCM 27671 Tries 15 G 6901
//"67,7,59,61"  // Start 6901 Step 27671 LCM 1687931 Tries 28 G 754018
//"67,x,7"  // Start 0 Step 67 LCM 469 Tries 4 G 201
//"67,x,7,59"  // Start 201 Step 469 LCM 27671 Tries 10 G 4422
//"67,x,7,59,61"  // Start 4422 Step 27671 LCM 1687931 Tries 29 G 779210
//"67,7"  // Start 0 Step 67 LCM 469 Tries 6 G 335
//"67,7,x,59"  // Start 335 Step 469 LCM 27671 Tries 35 G 16281
//"67,7,x,59,61"  // Start 16281 Step 27671 LCM 1687931 Tries 46 G 1261476
//"1789,37"  // Start 0 Step 1789 LCM 66193 Tries 18 G 30413
//"1789,37,47"  // Start 30413 Step 66193 LCM 3111071 Tries 20 G 1288080
//"1789,37,47,1889"  // Start 1288080 Step 3111071 LCM 5876813119 Tries 387 G 1202161486
//"19,x,x,x,x,x,x,x,x,41"  // Start 0 Step 19 LCM 779 Tries 7 G 114
//"19,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,521"  // Start 114 Step 779 LCM 405859 Tries 471 G 366244
//"19,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,521,x,x,x,x,x,x,x,23"  // Start 366244 Step 405859 LCM 9334757 Tries 5 G 1989680
//"19,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,521,x,x,x,x,x,x,x,23,x,x,x,x,x,x,x,x,17"  // Start 1989680 Step 9334757 LCM 158690869 Tries 12 G 104672007
//"19,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,521,x,x,x,x,x,x,x,23,x,x,x,x,x,x,x,x,17,x,x,x,x,x,x,x,x,x,x,x,29"  // Start 104672007 Step 158690869 LCM 4602035201 Tries 4 G 580744614
//"19,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,521,x,x,x,x,x,x,x,23,x,x,x,x,x,x,x,x,17,x,x,x,x,x,x,x,x,x,x,x,29,x,523"  // Start 580744614 Step 4602035201 LCM 2406864410123 Tries 37 G 166254011850
//"19,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,521,x,x,x,x,x,x,x,23,x,x,x,x,x,x,x,x,17,x,x,x,x,x,x,x,x,x,x,x,29,x,523"  // Start 166254011850 Step 2406864410123 LCM 2406864410123 Tries 1 G 166254011850
//"19,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,521,x,x,x,x,x,x,x,23,x,x,x,x,x,x,x,x,17,x,x,x,x,x,x,x,x,x,x,x,29,x,523,x,x,x,x,x,37"  // Start 166254011850 Step 2406864410123 LCM 89053983174551 Tries 34 G 79592779545909
"19,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,521,x,x,x,x,x,x,x,23,x,x,x,x,x,x,x,x,17,x,x,x,x,x,x,x,x,x,x,x,29,x,523,x,x,x,x,x,37,x,x,x,x,x,x,13"  // Start 79592779545909 Step 89053983174551 LCM 1157701781269163 Tries 8 G 702970661767766
      // clang-format on
      "\n");
#endif
   std::invoke([&in] {
      std::string ignoreLine;
      std::getline(in, ignoreLine);
   });
   in.imbue(std::locale{in.getloc(), new WsComma});
   auto const busses = std::invoke([&in] {
      std::vector<BusInfo> b;
      char c;
      for(std::uint_fast8_t i{}; in >> c;)
      {
         if(c == 'x' && ++i)
            continue;
         in.putback(c);
         BusInfo info;
         if(in >> info.id)
         {
            info.offset = i;
            b.push_back(info);
            ++i;
         }
      }
      return b;
   });

   auto const [minBus, maxBus] = minmax(
      busses, [](auto& l, auto& r) { return l.id < r.id; });
   auto const lcm = std::accumulate(
      begin(busses), end(busses), Timestamp{1}, [](auto a, auto& b) {
         return std::lcm(a, b.id);
      });
   std::cout << "The LCM is " << lcm << '\n';

   auto const startSeed = lcm / minBus.id;

   Timestamp t{79592779545909};  // {(startSeed) / maxBus.id * maxBus.id -
                                 // maxBus.offset};

   std::cout << "Starting at " << t << '\n';
   auto const isTimestampOK = [&t](BusInfo const& bus) {
      return (t + (bus.id - 1)) / bus.id * bus.id - bus.offset % bus.id == t;
   };
   std::uintmax_t iterations{1};
   for(int xyz{}; xyz < 1; ++xyz, t += maxBus.id)
   {
      std::uint16_t printer{};
      while(!all_of(busses, isTimestampOK))
      {
         t += 89053983174551;  // maxBus.id;
         if(false && iterations > 13)
         {
            std::cout << "FAILED, reached after " << iterations
                      << " iterations and timestamp " << t << std::flush;
            return EXIT_FAILURE;
         }
         if(!++printer) [[unlikely]]
            std::cout << '.';
         ++iterations;
      }
      std::cout << "Tried " << iterations
                << " times before finding the answer\n";

      std::cout << "Gold departure is " << t;

      std::cout << std::endl;
   }
   return EXIT_SUCCESS;
}
