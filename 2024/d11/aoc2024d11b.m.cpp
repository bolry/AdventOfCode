// https://adventofcode.com/2024/day/11#part2
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

#include <array>
#include <charconv>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace {

using Int = std::intmax_t;

using Map = std::unordered_map<Int, Int>;

std::array<Map, 76> gLookups;

Int blink(int times, Int val) {
  assert(0 <= times && times < gLookups.size());
  auto &lookup = gLookups[times];
  if (auto iter = lookup.find(val); iter != lookup.end())
    return iter->second;
  if (times == 0)
    return lookup[val] = 1;
  if (val == 0)
    return lookup[val] = blink(times - 1, 1);
  if (auto const str = std::to_string(val); str.size() % 2 == 0) {
    auto *beg = str.data();
    auto *mid = beg + str.size() / 2;
    auto *end = beg + str.size();
    auto readStoneId = [](char const *first, char const *last) {
      Int stoneId;
      [[maybe_unused]] auto [p, ec] = std::from_chars(first, last, stoneId);
      assert(ec == std::errc{} && p == last);
      return stoneId;
    };
    return blink(times - 1, readStoneId(beg, mid)) +
           blink(times - 1, readStoneId(mid, end));
  }
  return lookup[val] = blink(times - 1, val * 2024);
}

void solve2024day11b(std::istream &input) {
  Int cnt{};
  for (Int v; input >> v;) {
    cnt += blink(75, v);
  }

  std::println("Puzzle answer is {}.", cnt);
}
} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day11b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
