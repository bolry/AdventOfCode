// https://adventofcode.com/2016/day/4
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

#include <algorithm>
#include <numeric>
#include <regex>
#include <unordered_map>
#include <vector>

namespace r4s = std::ranges;

namespace {
std::regex const re{R"(([a-z-]+)-(\d+)\[([a-z]{5})\])"};

struct Room {
  std::string name;
  int secId{};
  std::string cksum;

  bool isReal() const noexcept {
    using Map = std::unordered_map<char, int>;
    using ValueType = std::pair<char, int>;
    Map map;
    for (auto ch : name)
      ++map[ch];
    std::vector<ValueType> values(map.begin(), map.end());
    r4s::partial_sort(values, values.begin() + 5, [](auto &a, auto &b) {
      return a.second > b.second || (a.second == b.second && a.first < b.first);
    });
    return std::equal(cksum.begin(), cksum.end(), values.begin(),
                      [](char a, auto &b) { return a == b.first; });
  }

  friend std::istream &operator>>(std::istream &is, Room &r) {
    std::string row;
    if (!(is >> row))
      return is;
    std::smatch m;
    [[maybe_unused]] bool isOk = std::regex_match(row, m, re);
    assert(isOk);
    r.name = m[1].str();
    std::erase(r.name, '-');
    r.secId = std::stoi(m[2].str());
    r.cksum = m[3].str();
    // std::println("{} {} {}", r.name, r.secId, r.cksum);
    return is;
  }
};

void solve2016day4a(std::istream &input) {
  std::println("Puzzle answer is {}",
               std::accumulate(std::istream_iterator<Room>(input), {}, 0,
                               [](int acc, auto &r) {
                                 return acc + r.isReal() * r.secId;
                               }));
}
} // namespace

int main(int argc, char *argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2016day4a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
