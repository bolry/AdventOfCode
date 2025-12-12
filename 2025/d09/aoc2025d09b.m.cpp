
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
Int best(Pnt const &p, std::span<Pnt const> const pnts) noexcept {
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
11,1
11,7
9,7
9,5
2,5
2,3
7,3
)END_DATA"};
  std::istringstream in{simp};
  // std::ifstream in{"../input.txt"};
  assert(in);
  (void)in.imbue(std::locale(in.getloc(), new CommaAsSpace));
  std::vector<Pnt> pnts{std::istream_iterator<Pnt>{in}, {}};
  assert(in.eof());
  {
    // scale down
    Int minX = std::numeric_limits<Int>::max();
    Int minY = std::numeric_limits<Int>::max();
    for (auto &p:pnts) {
      minX = std::min(minX, p.x);
      minY = std::min(minY, p.y);
    }
    std::println("Min x is {}\nMin y is {}", minX, minY);
    for (auto &p:pnts) {
      p.x-=minX;
      p.y-=minY;
    }
  }
  Int largest{};
  std::println("{}", largest);
}
