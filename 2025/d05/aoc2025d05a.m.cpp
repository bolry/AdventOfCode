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

#include <cassert>
#include <fstream>
#include <iostream>
#include <span>
#include <sstream>
#include <string>
#include <vector>

namespace {
struct Rng {
  unsigned long long from, to;
  friend std::istream &operator>>(std::istream &in, Rng &rng) {
    char dash{};
    in >> rng.from >> dash >> rng.to;
    assert(!in || dash == '-');
    return in;
  }
};

bool isFresh(std::span<Rng const> rngs, unsigned long long id) {
  for (auto const [from, to] : rngs) {
    if (from <= id && id <= to)
      return true;
  }
  return false;
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

  int cnt{};
  for (unsigned long long id; ifs >> id;) {
    cnt += isFresh(rngs, id);
  }
  assert(ifs.eof());
  std::cout << cnt << std::endl;
}
