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
} // namespace

int main() {
  [[maybe_unused]] constexpr char simp[]{R"__()__"};
  std::istringstream in{simp};
  // std::ifstream in{"../input.txt"};
  assert(in);
  (void)in.imbue(std::locale(in.getloc(), new CommaAsSpace));
  Int res{};
  assert(in.eof());
  std::println("{}", res);
}
