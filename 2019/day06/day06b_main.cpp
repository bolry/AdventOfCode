//#define _GLIBCXX_DEBUG
//#define _GLIBCXX_DEBUG_PEDANTIC
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {

bool constexpr kDebug = false;

struct CtypeWithWhitespaceRightParen : std::ctype<char> {
  static auto makeTable() {
    static std::vector v(classic_table(), classic_table() + table_size);
    v[')'] |= space;
    return v.data();
  }
  explicit CtypeWithWhitespaceRightParen(size_t refs = 0U)
      : ctype(makeTable(), false, refs) {}
};

struct Orbit {
  std::string center;
  std::string orb;

  friend std::istream &operator>>(std::istream &in, Orbit &orbit) {
    in >> orbit.center >> orbit.orb;
    return in;
  }
  friend std::ostream &operator<<(std::ostream &os, Orbit const &orbit) {
    os << orbit.center << " --> " << orbit.orb;
    return os;
  }
};

int findTo(std::vector<Orbit> const &orbits, std::string_view const from,
           std::string_view const to, int const depthFromStart) {
  auto matchCenter = [name = from](auto const &item) {
    return item.center == name;
  };
  for (auto iter = cbegin(orbits), last = cend(orbits);; ++iter) {
    iter = std::find_if(iter, last, matchCenter);
    if (iter == last) {
      break;
    }
    if (iter->orb == to) {
      return depthFromStart;
    }
    auto res = findTo(orbits, iter->orb, to, depthFromStart + 1);
    if (res != -1) {
      return res;
    }
  }
  return -1;
}

int bestDist(std::vector<Orbit> &orbits, std::string_view const from,
             std::string_view const to, int const depthFromStart) {
  // auto matchCenter = [name = from](auto const &item){return item.center ==
  // name; };
  auto matchOrb = [name = from](auto const &item) { return item.orb == name; };
  auto iter = std::find_if(cbegin(orbits), cend(orbits), matchOrb);
  auto const myCenter = iter->center;
  kDebug && std::cout << "Jump " << *iter << '\n';
  (void)orbits.erase(iter);

  int dist = findTo(orbits, myCenter, to, 0);
  if (dist != -1) {
    kDebug && std::cout << "Found from " << myCenter << " to " << to
                       << " at distance " << dist << '\n';
    return depthFromStart + dist;
  } else {
    kDebug && std::cout << "Going up one level from " << myCenter << '\n';
    return bestDist(orbits, myCenter, to, depthFromStart + 1);
  }
}
} // namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::ios_base::badbit | std::ios_base::eofbit |
                       std::ios_base::failbit);
  if (argc < 2) {
    throw std::runtime_error("need filename argument");
  }
  std::ifstream inFile(argv[1]);
  if (!inFile) {
    throw std::runtime_error("problem opening file " + std::string(argv[1]));
  }
  inFile.imbue(
      std::locale(std::cin.getloc(), new CtypeWithWhitespaceRightParen));

  using Iter = std::istream_iterator<Orbit>;
  std::vector<Orbit> orbits{Iter{inFile}, Iter{}};

  auto shortest = bestDist(orbits, "YOU", "SAN", 0);

  std::cout << "Number of jumps " << shortest << '\n';

  return EXIT_SUCCESS;
}
