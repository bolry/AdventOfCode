namespace {
constexpr auto prDebug = true;

struct CommaAsSpace : std::ctype<char> {
  static mask const *make_table() noexcept {
    static auto tbl = [] {
      std::array<mask, table_size> arr;
      std::copy_n(classic_table(), table_size, arr.data());
      arr[','] |= space; // comma as whitespace
      return arr;
    }();
    return tbl.data();
  }

  CommaAsSpace() : ctype{make_table()} {}
};

using Int = long long;

struct Machine {
  std::vector<bool> goalLights;
  std::vector<bool> lights;
  std::vector<std::string> buttons;
  std::string joltage;
  friend std::ostream &operator<<(std::ostream &os, Machine const &obj) {
    // os << "lights: " << obj.lights << " buttons: ";
    for (auto const &butt : obj.buttons)
      os << butt << ' ';
    return os << " joltage: " << obj.joltage;
  }
  friend std::istream &operator>>(std::istream &ins, Machine &obj) {
    Machine res;
    std::string lghts;
    if (ins >> lghts) {
      assert((lghts.starts_with('[') && lghts.ends_with(']')));
      for (auto it = next(lghts.begin()), eit = prev(lghts.end()); it != eit;
           ++it) {
        res.goalLights.push_back(*it == '#');
      }
    }
    for (std::string str; ins >> str;) {
      if (str.starts_with('{')) {
        assert(str.ends_with('}'));
        res.joltage = std::move(str);
        obj = std::move(res);
        return ins;
      } else {
        assert(str.starts_with('(') && str.ends_with(')'));
        res.buttons.push_back(std::move(str));
      }
    }
    return ins;
  }
};

} // namespace

int main() {
  [[maybe_unused]] constexpr char simp[]{R"__(
[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}
)__"};
  std::istringstream in{simp};
  // std::ifstream in{"../input.txt"};
  assert(in);
  // (void)in.imbue(std::locale(in.getloc(), new CommaAsSpace));
  for (std::istream_iterator<Machine> it{in}, e{}; it != e; ++it)
    if constexpr (prDebug)
      std::cout << *it << std::endl;
  assert(in.eof());
  std::println("{}", 42);
}
