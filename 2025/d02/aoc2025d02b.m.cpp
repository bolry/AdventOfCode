
namespace {
  constexpr bool prDebug{false};

  using Int = long long;

  struct CommaAsSpace : std::ctype<char> {
    static mask const *make_table() {
      static mask table[table_size];
      std::copy_n(classic_table(), table_size, table);
      table[','] |= space; // mark comma as whitespace
      return table;
    }

    CommaAsSpace() : ctype(make_table()) {
    }
  };

  constexpr bool repeats(std::string_view const seg, std::string_view const str) {
    auto const strLen = str.length();
    auto const segLen = seg.length();
    if (strLen % segLen != 0)
      return false;
    auto const cnt = strLen / segLen;
    for (std::size_t i{}; i != cnt; ++i)
      if (str.substr(i * segLen, segLen) != seg)
        return false;
    return true;
  }

  constexpr bool invalid(Int const i) {
    auto const str = std::to_string(i);
    std::string_view const sv{str};
    auto sz = std::midpoint({}, sv.length());
    while (sz)
      if (auto const seg = sv.substr({}, sz); repeats(seg, sv))
        return true;
      else
        --sz;
    return false;
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
  [[maybe_unused]] static constexpr char simp[] =
      "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,"
      "1698522-1698528,446443-446449,38593856-38593862,565653-565659,"
      "824824821-824824827,2121212118-2121212124";
  std::istringstream in{simp};
  // std::ifstream in("../input.txt");
  assert(in);
  (void) in.imbue(std::locale(in.getloc(), new CommaAsSpace));
  Int grandSum{};
  Int a, b;
  for (char dash; in >> a >> dash >> b; dash = {}) {
    assert(dash == '-' && a < b);
    if constexpr (prDebug)
      std::print("{} {} ", a, b);
    auto s = sum(a, b);
    if constexpr (prDebug)
      std::println("{}", s);
    grandSum += s;
  }
  std::println("{}", grandSum);
  return 0;
}
