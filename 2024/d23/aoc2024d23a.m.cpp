// https://adventofcode.com/2024/day/23
// C++23
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <new>
#include <print>

#include <map>
#include <set>
#include <string>

namespace {

using Computer = std::string;

struct Connection {
  Computer m0, m1;

  friend std::istream &operator>>(std::istream &is, Connection &obj) {
    if (not(is >> obj.m0)) {
      assert(is.eof());
      return is;
    }
    assert(obj.m0.size() == 5 && obj.m0[2] == '-');
    obj.m1 = obj.m0.substr(3);
    obj.m0.resize(2);
    assert(obj.m0 != obj.m1);
    return is;
  }
};

void solve2024day23a(std::istream &input) {
  std::map<Computer, std::set<Computer>> map;
  for (Connection con; input >> con;) {
    map[con.m0].insert(con.m1);
    map[con.m1].insert(con.m0);
  }
  assert(input.eof());

  std::set<std::set<Computer>> result;

  for (auto b = map.lower_bound("ta"), e = map.upper_bound("tz"); b != e; ++b)
    for (auto f = b->second.begin(), fEnd = b->second.end(); f != fEnd; ++f)
      for (auto snd = std::next(f); snd != fEnd; ++snd)
        if (map[*f].contains(*snd))
          result.insert({b->first, *f, *snd});

  std::println("Puzzle answer is {}.", result.size());
}

} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day23a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
