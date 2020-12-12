#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std::literals;
using namespace std::ranges;

namespace
{
using Row = std::string;
using Map = std::vector<Row>;

std::ostream& operator<<(std::ostream& os, Map const& map)
{
   for_each(map, [](Row const& row) { std::cout << row << '\n'; });
   return os;
}

constexpr auto kOcc{'#'};
constexpr auto kEmp{'L'};
constexpr auto kFlo{'.'};

auto countFarAround(Map const& m, int const x, int const y)
{
   auto const height{ssize(m) - 1};
   auto const width{ssize(m.front()) - 1};
   std::size_t cnt{};
   for(auto xz = x, yz = y; xz-- && yz--;)  // upper left
      if(m[yz][xz] == kOcc && ++cnt || m[yz][xz] == kEmp)
         break;
   for(auto yz = y; yz--;)  // above
      if(m[yz][x] == kOcc && ++cnt || m[yz][x] == kEmp)
         break;
   for(auto xz = x, yz = y; xz++ < width && yz--;)  // upper right
      if(m[yz][xz] == kOcc && ++cnt || m[yz][xz] == kEmp)
         break;
   for(auto xz = x; xz--;)  // left
      if(m[y][xz] == kOcc && ++cnt || m[y][xz] == kEmp)
         break;
   for(auto xz = x; xz++ < width;)  // right
      if(m[y][xz] == kOcc && ++cnt || m[y][xz] == kEmp)
         break;
   for(auto xz = x, yz = y; xz-- && yz++ < height;)  // lower left
      if(m[yz][xz] == kOcc && ++cnt || m[yz][xz] == kEmp)
         break;
   for(auto yz = y; yz++ < height;)  // below
      if(m[yz][x] == kOcc && ++cnt || m[yz][x] == kEmp)
         break;
   for(auto xz = x, yz = y; xz++ < width && yz++ < height;)  // lower right
      if(m[yz][xz] == kOcc && ++cnt || m[yz][xz] == kEmp)
         break;
   return cnt;
}

void nextRound(Map const& oldRound, Map& newRound)
{
   int const height{ssize(oldRound)};
   int const width{ssize(oldRound.front())};
   for(int y{}; y < height; ++y)
      for(int x{}; x < width; ++x)
         if(auto& op = oldRound[y][x]; op != kFlo)
            if(auto& np       = newRound[y][x];
               auto const cnt = countFarAround(oldRound, x, y))
               if(cnt >= 5)
                  np = kEmp;
               else
                  np = op;
            else
               np = kOcc;
}

int countSeats(Map const& map)
{
   return std::accumulate(cbegin(map), cend(map), 0, [](int a, Row const& str) {
      return a + count(str, kOcc);
   });
}
}  // namespace

int main()
{
   std::ifstream in("../input.txt");
   Map map(std::istream_iterator<Row>{in}, std::istream_iterator<Row>{});
   Map nextMap = map;
   for(int round{};; ++round)
   {
      constexpr bool kTrace{false};
      kTrace&& std::cout << "Round " << round << '\n' << map << '\n';
      nextRound(map, nextMap);
      if(map == nextMap)
         break;
      swap(map, nextMap);
   }
   std::cout << countSeats(map) << '\n' << std::flush;
   return EXIT_SUCCESS;
}
