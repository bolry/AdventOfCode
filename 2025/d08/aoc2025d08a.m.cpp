
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

using Int = int;

struct JB {
  Int x, y, z;

  auto operator<=>(JB const &) const = default;

  friend std::istream &operator>>(std::istream &in, JB &obj) {
    return in >> obj.x >> obj.y >> obj.z;
  }
  friend std::ostream &operator<<(std::ostream &os, JB const &obj) {
    return os << "x: " << std::setw(5) << obj.x << " y: " << std::setw(5)
              << obj.y << " z: " << std::setw(5) << obj.z;
  }
};

struct Dist {
  double distance;
  std::size_t jbIdx1, jbIdx2;
  auto operator<=>(Dist const &) const = default;
};

auto dist(JB const &a, JB const &b) {
  return std::hypot(a.x - b.x, a.y - b.y, a.z - b.z);
}
} // namespace
int main() {
  [[maybe_unused]] constexpr char simp[]{
      R"END_DATA(
162,817,812
57,618,57
906,360,560
592,479,940
352,342,300
466,668,158
542,29,236
431,825,988
739,650,466
52,470,668
216,146,977
819,987,18
117,168,530
805,96,715
346,949,466
970,615,88
941,993,340
862,61,35
984,92,344
425,690,689
)END_DATA"};
  std::istringstream in{simp};
  // std::ifstream in{"../input.txt"};
  assert(in);
  (void)in.imbue(std::locale(in.getloc(), new CommaAsSpace));
  std::vector const jbs(std::istream_iterator<JB>{in}, {});
  assert(in.eof());
  // std::ranges::sort(jbs);
  if constexpr (prDebug)
    for (auto const &jb : jbs)
      std::cout << jb << '\n';

  std::vector<Dist> dists;
  assert(not jbs.empty());
  for (std::size_t i{}; i != jbs.size() - 1u; ++i) {
    for (auto j = i + 1u; j != jbs.size(); ++j) {
      auto [min, max] = std::minmax(i, j, [&jbs](std::size_t a, std::size_t b) {
        return jbs[a] < jbs[b];
      });
      dists.push_back(Dist{dist(jbs[i], jbs[j]), min, max});
    }
  }
  std::ranges::sort(dists);
  if constexpr (prDebug)
    for (auto const &d : dists)
      std::println("Dist {} ({}, {}, {}) => ({}, {}, {})", d.distance,
                   jbs[d.jbIdx1].x, jbs[d.jbIdx1].y, jbs[d.jbIdx1].z,
                   jbs[d.jbIdx2].x, jbs[d.jbIdx2].y, jbs[d.jbIdx2].z);
  std::println("{}", jbs.size());
}
