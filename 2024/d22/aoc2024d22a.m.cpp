// https://adventofcode.com/2024/day/22
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

#include <iterator>
#include <numeric>

namespace {

using Int = unsigned int;

static_assert((42u ^ 15u) == 37u);                        // mix
static_assert(100'000'000u % 16'777'216u == 16'113'920u); // prune

constexpr Int next(Int const old) {
  auto const n1 = ((old * 64u) ^ old) % 16'777'216u;
  auto const n2 = ((n1 / 32u) ^ n1) % 16'777'216u;
  auto const n3 = ((n2 * 2048u) ^ n2) % 16'777'216u;
  return n3;
}
static_assert(next(123) == 15'887'950);
static_assert(next(15'887'950) == 16'495'136);
static_assert(next(16'495'136) == 527'345);
static_assert(next(527'345) == 704'524);
static_assert(next(704'524) == 1'553'684);
static_assert(next(1'553'684) == 12'683'156);
static_assert(next(12'683'156) == 11'100'544);
static_assert(next(11'100'544) == 12'249'484);
static_assert(next(12'249'484) == 7'753'432);
static_assert(next(7'753'432) == 5'908'254);

constexpr Int next(Int sec, int nth) {
  assert(nth >= 0);
  while (nth--)
    sec = next(sec);
  return sec;
}
static_assert(next(123, 10) == 5908254);

void solve2024day22a(std::istream &input) {

  auto sum = std::accumulate(
      std::istream_iterator<Int>(input), {}, Int{},
      [](Int acc, Int secret) { return acc + next(secret, 2'000); });

  std::println("Puzzle answer is {}.", sum);
}

} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day22a(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
