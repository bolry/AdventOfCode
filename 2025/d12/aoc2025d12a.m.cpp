
namespace {
  constexpr auto prDebug = true;

  struct CommaAsSpace : std::ctype<char> {
    static mask const *make_table() noexcept {
      static auto tbl = [] {
        std::array<mask, table_size> arr{};
        std::copy_n(classic_table(), table_size, arr.data());
        arr[','] |= space; // comma as whitespace
        return arr;
      }();
      return tbl.data();
    }

    CommaAsSpace() : ctype{make_table()} {
    }
  };

  using Int = long long;

} // namespace

int main() {
  [[maybe_unused]] constexpr char simp[]{
    R"__()__"
  };
  std::istringstream in{simp};
  // std::ifstream in{"../input.txt"};
  assert(in);
  // (void)in.imbue(std::locale(in.getloc(), new CommaAsSpace));
  assert(in.eof());
  std::println("{}", 42);
}
