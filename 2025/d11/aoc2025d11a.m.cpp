
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

  using Name = std::string;

  struct Dev {
    Name name;
    std::vector<Name> outputs;

    friend std::ostream &operator<<(std::ostream &os, Dev const &obj) {
      os << "name: " << obj.name << " outputs: ";
      for (auto &out: obj.outputs) os << out;
      return os;
    }

    friend std::istream &operator>>(std::istream &in, Dev &obj) {
      if (std::string line; std::getline(in, line)) {
        std::istringstream iss(line);
        obj = {};
        iss >> obj.name;
        assert(obj.name.ends_with(':'));
        obj.name.pop_back();
        while (iss >> line)
          obj.outputs.push_back(line);
      }
      return in;
    }
  };
} // namespace

int main() {
  [[maybe_unused]] constexpr char simp[]{
    R"__(aaa: you hhh
you: bbb ccc
bbb: ddd eee
ccc: ddd eee fff
ddd: ggg
eee: out
fff: out
ggg: out
hhh: ccc fff iii
iii: out
)__"
  };
  std::istringstream in{simp};
  // std::ifstream in{"../input.txt"};
  assert(in);
  // (void)in.imbue(std::locale(in.getloc(), new CommaAsSpace));
  for (Dev dev; in >> dev;) {
    std::cout << dev << '\n';
  }
  assert(in.eof());
  std::println("{}", 42);
}
