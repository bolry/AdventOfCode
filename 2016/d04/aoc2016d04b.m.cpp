// https://adventofcode.com/2016/day/4#part2
// C++23
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <new>
#include <print>

#include <regex>
#include <string>

namespace {

std::regex const re{R"(([a-z-]+)-(\d+)\[[a-z]{5}\])"};

struct Room {
  std::string raw;
  int secId{};

  [[nodiscard]] std::string decrypt() const {
    std::string str;
    str.reserve(raw.size());
    for (int ch : raw)
      if (ch == '-')
        str += ' ';
      else
        str += static_cast<char>((ch - 'a' + secId) % 26 + 'a');
    return str;
  }

  friend std::istream &operator>>(std::istream &is, Room &r) {
    if (std::string row; is >> row) {
      std::smatch m;
      [[maybe_unused]] bool isOk = std::regex_match(row, m, re);
      assert(isOk);
      r.raw = m[1].str();
      r.secId = std::stoi(m[2].str());
    }
    return is;
  }
};

void solve2016day4b(std::istream &input) {
  for (Room room; input >> room;)
    std::println("{} id: {}", room.decrypt(), room.secId);
}
} // namespace

int main(int argc, char *argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2016day4b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
