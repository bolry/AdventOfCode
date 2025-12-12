#ifdef NDEBUG
#undef NDEBUG
#endif

#ifndef _GLIBCXX_DEBUG
#define _GLIBCXX_DEBUG
#endif

#ifndef _GLIBCXX_DEBUG_PEDANTIC
#define _GLIBCXX_DEBUG_PEDANTIC
#endif

#ifndef _GLIBCXX_ASSERTIONS
#define _GLIBCXX_ASSERTIONS
#endif

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iterator>
#include <numeric>
#include <iostream>
#include <ranges>
#include <sstream>

namespace {
  struct Rotation {
    bool isLeft; // or Right
    int steps;

    friend std::istream &operator>>(std::istream &os, Rotation &obj) {
      if (auto dir = 'x'; os >> dir >> obj.steps) {
        assert(dir=='L' || dir=='R');
        obj.isLeft = dir == 'L';
      }
      return os;
    }
  };
} // namespace

int main() {
  namespace r4s = std::ranges;
  [[maybe_unused]] constexpr char simp[]{
    "L68 L30 R48 L5 R60 L55 L1 L99 R14 L82"
  };
  // std::istringstream in{simp};
  std::ifstream in{"../input.txt"};
  int pos = 50;
  auto rotationsPastZero = [&p = pos](int acc, Rotation const &mv) {
    assert(0 <= p && p < 100);
    if (mv.isLeft) {
      for (int i{}; i != mv.steps; ++i) {
        --p;
        if (p == 0) ++acc;
        else
          if (p < 0) p = 99;
      }
    } else {
      for (int i{}; i != mv.steps; ++i) {
        ++p;
        if (p == 100) {
          p = 0;
          ++acc;
        }
      }
    }
    assert(0 <= p && p < 100);
    return acc;
  };
  std::cout << std::accumulate(std::istream_iterator<Rotation>{in}, {}, int{}, rotationsPastZero);
}
