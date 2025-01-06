// https://adventofcode.com/2024/day/22#part2
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
#include <array>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

namespace {

namespace r4s = std::ranges;

using Int = std::uintmax_t;
using Price = std::int8_t;

constexpr Int next(Int n) noexcept {
  n = ((n * 64u) ^ n) % 16'777'216u;
  n = ((n / 32u) ^ n) % 16'777'216u;
  n = ((n * 2'048u) ^ n) % 16'777'216u;
  return n;
}

constexpr Int next(Int sec, int nth) noexcept {
  assert(nth >= 0);
  while (nth--)
    sec = next(sec);
  return sec;
}
static_assert(next(123, 10) == 5'908'254);

using Seq = std::array<Price, 4>;
struct SeqHash {
  auto operator()(Seq const &obj) const noexcept {
    return std::hash<std::int32_t>{}(
        *reinterpret_cast<std::int32_t const *>(obj.data()));
  }
};

void solve2024day22b(std::istream &input) {
  std::unordered_map<Seq, int, SeqHash> payoffs;
  for (Int secret; input >> secret;) {
    Price price = secret % 10;
    Seq seq;
    // std::println("{:>8}: {}", secret, secret % 10);
    for (int i{}; i != 4; ++i) {
      secret = next(secret);
      Price newPrice = secret % 10;
      Price diff = newPrice - price;
      seq[i] = diff;
      // std::println("{:>8}: {} ({})", secret, newPrice, diff);
      price = newPrice;
    }
    std::unordered_set<Seq, SeqHash> seenSeq{seq};
    payoffs[seq] += price;
    for (int i{4}; i != 2'000; ++i) {
      secret = next(secret);
      auto oldPrice = price;
      price = secret % 10;
      r4s::shift_left(seq, 1);
      seq.back() = price - oldPrice;
      auto [_, isNewSeq] = seenSeq.insert(seq);
      if (isNewSeq)
        payoffs[seq] += price;
    }
  }
  auto bestSeq = r4s::max_element(
      payoffs, [](auto &a, auto &b) { return a.second < b.second; });
  std::println("Puzzle answer is {}.", bestSeq->second);
}

} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day22b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
