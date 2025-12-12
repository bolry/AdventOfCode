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
#include <iterator>
#include <span>
#include <sstream>
#include <string>
#include <vector>

namespace {
using U = unsigned long long;
struct Rng {
  U from, to;
  friend std::istream &operator>>(std::istream &in, Rng &rng) {
    char dash{};
    in >> rng.from >> dash >> rng.to;
    assert(!in || dash == '-' && rng.from <= rng.to);
    return in;
  }
  auto operator<=>(Rng const &) const = default;
};

void reduce(std::vector<Rng> &rngs) {
  std::ranges::sort(rngs);
  if (rngs.size() < 2)
    return;
  auto it = rngs.begin();
  auto nxt = std::next(it);
  while (nxt != rngs.end())
    if (it->to < nxt->from)
      ++it, ++nxt;
    else if (it->to >= nxt->to)
      nxt = rngs.erase(nxt);
    else
      it->to = nxt->to, nxt = rngs.erase(nxt);
}

} // namespace
int main() {
  [[maybe_unused]] constexpr char simp[]{R"(3-5
10-14
16-20
12-18

1
5
8
11
17
32
)"};
  // std::istringstream ifs{simp};
  std::ifstream ifs{"../input.txt"};
  assert(ifs);

  std::vector<Rng> rngs;
  for (std::string line; std::getline(ifs, line) && not line.empty();) {
    std::istringstream ifsline{line};
    Rng rng;
    if (ifsline >> rng)
      rngs.push_back(rng);
    else
      assert(false);
  }
  assert(ifs);

  U cnt{};
  reduce(rngs);
  for (auto const &[from, to] : rngs) {
    cnt += to - from + 1;
  }
  std::cout << cnt << std::endl;
}
