#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <string>
#include <unordered_map>

using namespace std::literals;

namespace
{
struct Line
{
   std::string line;
   operator std::string() const
   {
      return line;
   }
   friend std::istream& operator>>(std::istream& in, Line& line)
   {
      std::getline(in, line.line);
      return in;
   }
};
}  // namespace

int main()
{
   std::unordered_map<std::string, std::uint16_t> wires;
   std::ifstream in("../input2.txt"s);
   std::vector<std::string> v(
      std::istream_iterator<Line>{in}, std::istream_iterator<Line>{});
   return EXIT_SUCCESS;
}
