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

int countOrbits(std::vector<Orbit> const &orbits, std::string_view const name,
                int const cnt) {
  int res{cnt};
  auto last = cend(orbits);
  for (auto iter = cbegin(orbits);; ++iter) {
    iter = std::find_if(
        iter, last, [name](auto const &item) { return item.center == name; });
    if (iter == last) {
      break;
    }
    res += countOrbits(orbits, iter->orb, cnt + 1);
  }
  std::cout << name << ' ' << res << '\n';
  return res;
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
  std::vector<Orbit> const orbits{Iter{inFile}, Iter{}};

  auto const cnt = countOrbits(orbits, "COM", 0);
  std::cout << "Total " << cnt << '\n';

  return EXIT_SUCCESS;
}
