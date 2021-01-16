#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <unordered_map>

using namespace std::ranges;

namespace
{
using Id       = int;
using EdgeHash = std::uint_least16_t;
struct Tile
{
   Id id;
   std::array<EdgeHash, 8> edgeHashes;
   friend std::istream& operator>>(std::istream& in, Tile& tile)
   {
      std::string chunk;
      if(in >> chunk >> tile.id >> chunk)
         assert(chunk == ":");
      else
         return in;
      constexpr std::string::size_type sideLen{10};
      std::string top(sideLen, '\0');
      auto left  = top;
      auto right = top;
      std::string bottom;
      for(std::remove_const_t<decltype(sideLen)> i{}; i < sideLen; ++i)
      {
         if(in >> bottom)
            assert(bottom.length() == sideLen);
         else
            return in;
         if(i == 0)
            top = bottom;
         left[i]  = bottom.front();
         right[i] = bottom.back();
      }
      constexpr auto str2EdgeHash = [](std::string const& s) {
         constexpr auto zero = '.';
         constexpr auto one  = '#';
         std::bitset<sideLen> bs(s, 0, std::string::npos, zero, one);
         return static_cast<EdgeHash>(bs.to_ulong());
      };
      tile.edgeHashes[0] = str2EdgeHash(top);
      tile.edgeHashes[1] = str2EdgeHash(left);
      tile.edgeHashes[2] = str2EdgeHash(right);
      tile.edgeHashes[3] = str2EdgeHash(bottom);
      reverse(top);
      tile.edgeHashes[4] = str2EdgeHash(top);
      reverse(left);
      tile.edgeHashes[5] = str2EdgeHash(left);
      reverse(right);
      tile.edgeHashes[6] = str2EdgeHash(right);
      reverse(bottom);
      tile.edgeHashes[7] = str2EdgeHash(bottom);
      return in;
   }
};
}  // namespace
int main()
{
   struct X
   {
      int cnt;
      Id lastIdSeen;
   };
   std::unordered_map<EdgeHash, X> x;
   {
      std::ifstream in("../input.txt");
      auto first = std::istream_iterator<Tile>{in};
      auto last  = std::istream_iterator<Tile>{};
      for(; first != last; ++first)
         for(auto const& hash : first->edgeHashes)
         {
            auto& item = x[hash];
            ++item.cnt;
            item.lastIdSeen = first->id;
         }
   }
   for(auto const& hmm : x)
   {
      if(hmm.second.cnt == 1)
         std::cout << hmm.second.lastIdSeen << '\n';
   }
   std::cout << std::endl;
}
