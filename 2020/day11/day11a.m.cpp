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

auto countAround(Map const& m, int x, int y)
{
   auto const height{ssize(m) - 1};
   auto const width{ssize(m.front()) - 1};
   std::size_t cnt{};
   if(x && y)  // upper left
      cnt += m[y - 1][x - 1] == kOcc;
   if(y)  // above
      cnt += m[y - 1][x] == kOcc;
   if(x < width && y)  // upper right
      cnt += m[y - 1][x + 1] == kOcc;
   if(x)  // left
      cnt += m[y][x - 1] == kOcc;
   if(x < width)  // right
      cnt += m[y][x + 1] == kOcc;
   if(x && y < height)  // lower left
      cnt += m[y + 1][x - 1] == kOcc;
   if(y < height)  // below
      cnt += m[y + 1][x] == kOcc;
   if(x < width && y < height)  // lower right
      cnt += m[y + 1][x + 1] == kOcc;
   return cnt;
}

void nextRound(Map const& oldRound, Map& newRound)
{
   int const height{ssize(oldRound)};
   int const width{ssize(oldRound.front())};
   for(int y{}; y < height; ++y)
      for(int x{}; x < width; ++x)
         if(oldRound[y][x] != kFlo)
            if(auto const cnt = countAround(oldRound, x, y); cnt >= 4)
               newRound[y][x] = kEmp;
            else if(cnt == 0)
               newRound[y][x] = kOcc;
            else
               newRound[y][x] = oldRound[y][x];
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
