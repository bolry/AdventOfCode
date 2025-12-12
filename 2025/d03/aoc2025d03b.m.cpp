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
  //  std::istringstream ifs{simp};
  std::ifstream ifs{"../input.txt"};
  assert(ifs);
  unsigned long long sum{};
  using Bank = std::string;
  for (Bank bnk; ifs >> bnk;) {
    // std::cout << '`' << bnk << "'\n";
    auto max1Iter = max_element(bnk.begin(), prev(bnk.end(), 11));
    auto max2Iter = max_element(next(max1Iter), prev(bnk.end(), 10));
    auto max3Iter = max_element(next(max2Iter), prev(bnk.end(), 9));
    auto max4Iter = max_element(next(max3Iter), prev(bnk.end(), 8));
    auto max5Iter = max_element(next(max4Iter), prev(bnk.end(), 7));
    auto max6Iter = max_element(next(max5Iter), prev(bnk.end(), 6));
    auto max7Iter = max_element(next(max6Iter), prev(bnk.end(), 5));
    auto max8Iter = max_element(next(max7Iter), prev(bnk.end(), 4));
    auto max9Iter = max_element(next(max8Iter), prev(bnk.end(), 3));
    auto max10Iter = max_element(next(max9Iter), prev(bnk.end(), 2));
    auto max11Iter = max_element(next(max10Iter), prev(bnk.end(), 1));
    auto max12Iter = max_element(next(max11Iter), prev(bnk.end(), 0));
    std::string const res{*max1Iter, *max2Iter,  *max3Iter,  *max4Iter,
                          *max5Iter, *max6Iter,  *max7Iter,  *max8Iter,
                          *max9Iter, *max10Iter, *max11Iter, *max12Iter};
    unsigned long long bankJolage = std::stoull(res);
    sum += bankJolage;
  }
  std::cout << sum << std::endl;
}
