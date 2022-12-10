#include <algorithm>
#include <cassert>
#include <charconv>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

namespace
{
using namespace std::string_view_literals;
using Uint = unsigned long long;
using Map  = std::unordered_map<std::string, Uint>;
using Set  = std::unordered_set<std::string>;
}  // namespace

int main()
{
   std::ifstream ifs("../input.txt");
   assert(ifs);
   std::string cwd;
   Set dirNames;
   Map files;
   for(std::string line; std::getline(ifs, line);)
   {
      if(line == "$ cd .."sv)
      {
         assert(not cwd.empty());  // moving above root, /
         cwd.pop_back();
         cwd.resize(cwd.find_last_of('/') + 1u);
         std::cout << "up to `" << cwd << "'\n";
      }
      else if(line == "$ cd /"sv)
      {
         cwd.clear();
         std::cout << "now in `' aka /\n";
      }
      else if(line.starts_with("$ cd "sv))
      {
         cwd += line.substr(5) + '/';
         std::cout << "down in `" << cwd << "'\n";
      }
      else if(line == "$ ls"sv)
      {
      }
      else if(line.starts_with("dir "sv))
      {
         auto [iter, isInserted] = dirNames.insert(cwd + line.substr(4) + '/');
         if(not isInserted)
            std::cout << "DUPLICATE `" << *iter << "'\n";
      }
      else  // size & filename
      {
         int sz;
         auto [ptr, ec] = std::from_chars(
            line.data(), line.data() + line.size(), sz);
         assert(ec == std::errc{});
         assert(*ptr == ' ');
         ++ptr;
         files[cwd + ptr] = sz;
      }
   }
   // get dir sizes
   Map dirSizes;
   for(auto const& d : dirNames)
   {
      Uint sz{};
      for(auto const& f : files)
         if(f.first.starts_with(d))
            sz += f.second;
      dirSizes[d] = sz;
   }
   Uint sum{};
   for(auto const& d : dirSizes)
      if(d.second <= 100000)
         sum += d.second;
   std::cout << "Grand total " << sum << std::endl;
   return EXIT_SUCCESS;
}
