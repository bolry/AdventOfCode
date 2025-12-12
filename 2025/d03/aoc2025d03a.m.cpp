#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

int main() {
  [[maybe_unused]] constexpr char simp[]{R"(987654321111111
811111111111119
234234234234278
818181911112111
)"};
  // std::istringstream ifs{simp};
  std::ifstream ifs{"../input.txt"};
  assert(ifs);
  int sum{};
  using Bank = std::string;
  for (Bank bnk; ifs >> bnk;) {
    // std::cout << '`' << bnk << "'\n";
    auto max1Iter = max_element(bnk.begin(), prev(bnk.end()));
    auto max2Iter = max_element(next(max1Iter), bnk.end());
    std::string const res{*max1Iter, *max2Iter};
    int bankJolage = std::stoi(res);
    sum += bankJolage;
  }
  std::cout << sum << std::endl;
}
