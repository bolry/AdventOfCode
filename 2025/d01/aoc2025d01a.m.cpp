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
  std::istringstream in{simp};
  // std::ifstream in{"../input.txt"};
  int pos = 50;
  auto rotatesToZero = [&p = pos](Rotation const &mv) {
    if (mv.isLeft) {
      p -= mv.steps % 100;
      if (p < 0) p += 100;
    } else {
      p += mv.steps % 100;
      p %= 100;
    }
    return p == 0;
  };
  std::cout << r4s::count_if(r4s::istream_view<Rotation>{in}, rotatesToZero);
}
