#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>

namespace
{
std::map<char, int> translateDirection{{'(', 1}, {')', -1}};
}
int main()
{
   std::ifstream in("../input.txt");
   int const theFloor = std::accumulate(
      std::istream_iterator<char>(in),
      std::istream_iterator<char>(),
      0,
      [](int a, char b) { return a + translateDirection[b]; });
   std::cout << "Santa exits on floor " << theFloor << std::endl;
}
