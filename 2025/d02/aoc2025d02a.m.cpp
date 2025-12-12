
namespace {
constexpr bool prDebug{false};

using Int = std::int_least64_t;

struct CommaAsSpace final : std::ctype<char> {
  static mask const *make_table() noexcept {
    static mask tbl[table_size];
    std::copy_n(classic_table(), table_size, tbl);
    tbl[','] |= space; // comma as whitespace
    return tbl;
  }

  CommaAsSpace() : ctype{make_table()} {}
};

constexpr bool invalid(Int const i) {
  auto const str = std::to_string(i);
  std::string_view const sv{str};
  auto const mid = std::midpoint({}, sv.length());
  auto const first = sv.substr({}, mid);
  auto const last = sv.substr(mid);
  return first == last;
}

constexpr Int sum(Int const a, Int const b) {
  Int s{};
  for (Int i{a}; i <= b; ++i)
    if (invalid(i))
      s += i;
  return s;
}
} // namespace

int main() {
  [[maybe_unused]] static constexpr char simp[]{
      "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,"
      "1698522-1698528,446443-446449,38593856-38593862,565653-565659,"
      "824824821-824824827,2121212118-2121212124"};
  std::istringstream in{simp};
  // std::ifstream in("../input.txt");
  assert(in);
  (void)in.imbue(std::locale(in.getloc(), new CommaAsSpace));
  Int grandSum{};
  Int a, b;
  for (char dash{}; in >> a >> dash >> b; dash = {}) {
    assert(dash == '-' && a < b);
    if constexpr (prDebug)
      std::print("{} {} ", a, b);
    auto s = sum(a, b);
    if constexpr (prDebug)
      std::println("{}", s);
    grandSum += s;
  }
  std::cout << grandSum << std::endl;
  return EXIT_SUCCESS;
}
