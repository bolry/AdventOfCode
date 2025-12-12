
#include <ostream>

namespace {
constexpr auto prDebug = true;

struct CommaAsSpace : std::ctype<char> {
  static mask const *make_table() noexcept {
    static mask tbl[table_size];
    std::copy_n(classic_table(), table_size, tbl);
    tbl[','] |= space; // comma as whitespace
    return tbl;
  }

  CommaAsSpace() : ctype{make_table()} {}
};

using Int = long long;

struct Pnt {
  Int x, y;

  friend std::ostream &operator<<(std::ostream &os, Pnt const &obj) {
    return os << "x: " << obj.x << " y: " << obj.y;
  }

  friend std::istream &operator>>(std::istream &os, Pnt &obj) {
    return os >> obj.x >> obj.y;
  }
};
constexpr auto area(Pnt const &a, Pnt const &b) {
  using std::abs;
  return (abs(a.x - b.x) + 1) * (abs(a.y - b.y) + 1);
}
// static_assert(area({7,1}, {7,1}) == 1);
// static_assert(area({2, 5}, {9, 7}) == 24);
// static_assert(area( {9, 7}, {2, 5}) == 24);
// static_assert(area({7, 1}, {11, 7}) == 35);
Int best(Pnt const &p, std::vector<Pnt> const &pnts) noexcept {
  auto cmp = [&p](Pnt const &a, Pnt const &b) {
    return area(a, p) < area(b, p);
  };
  if (auto const iter = std::ranges::max_element(pnts, cmp); iter != pnts.end())
    return area(p, *iter);
  else
    return 0;
}

} // namespace
int main() {
  [[maybe_unused]] constexpr char simp[]{
      R"END_DATA(
7,1
9,3
11,7
)END_DATA"};
  // std::istringstream in{simp};
  std::ifstream in{"../input.txt"};
  assert(in);
  (void)in.imbue(std::locale(in.getloc(), new CommaAsSpace));
  Int largest{};
  std::vector<Pnt> pnts;
  for (Pnt pnt; in >> pnt;) {
    auto now = best(pnt, pnts);
    largest = std::max(now, largest);
    pnts.push_back(pnt);
  }
  assert(in.eof());
  std::println("{}", largest);
}
// 2147443320 too low
// 4750092396