// https://adventofcode.com/2024/day/24#part2
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
#include <cstdint>
#include <iostream>
#include <limits>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <utility>

namespace {
using Int = std::uintmax_t;

using namespace std::literals::string_view_literals;

struct Wire {
  std::string name;
  bool val;

  auto operator<=>(Wire const &other) const noexcept {
    return name <=> other.name;
  }

  friend std::istream &operator>>(std::istream &is, Wire &obj) {
    auto &line = obj.name;
    std::getline(is, line);
    assert(is);
    if (line.empty()) [[unlikely]] {
      is.setstate(is.failbit);
      return is;
    }
    constexpr std::size_t colPos{3};
    constexpr std::size_t bPos{5};
    assert(line[colPos] == ':' and (line[bPos] == '0' or line[bPos] == '1'));
    obj.val = line[bPos] == '1';
    obj.name.resize(colPos);
    return is;
  }
};

using Wires = std::set<Wire>;

constexpr bool _and(bool a, bool b) noexcept { return a and b; }
constexpr bool _or(bool a, bool b) noexcept { return a or b; }
constexpr bool _xor(bool a, bool b) noexcept { return a xor b; }

using Logic = bool (*)(bool, bool) noexcept;

struct Gate {
  std::string inA, inB, out;
  Logic op;

  auto operator<=>(Gate const &other) const noexcept {
    return out <=> other.out;
  }

  friend std::istream &operator>>(std::istream &is, Gate &obj) {
    if (not(is >> obj.inA)) [[unlikely]] {
      assert(is.eof());
      return is;
    }
    std::string op;
    is >> op >> obj.inB;
    if (obj.inB < obj.inA)
      obj.inA.swap(obj.inB);
    if (op == "AND"sv)
      obj.op = _and;
    else if (op == "XOR"sv)
      obj.op = _xor;
    else if (op == "OR"sv)
      obj.op = _or;
    else [[unlikely]]
      assert(false);

    is.ignore(std::numeric_limits<std::streamsize>::max(), '>');
    assert(is);
    is >> obj.out;
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, Gate const &obj) {
    os << obj.inA;
    if (obj.op == _and)
      os << " AND ";
    else if (obj.op == _xor)
      os << " XOR ";
    else if (obj.op == _or)
      os << " OR ";
    else [[unlikely]]
      assert(false);
    os << obj.inB << " -> " << obj.out;
    return os;
  }
};

using Gates = std::set<Gate>;

bool lookupVal(std::string_view name, Gates const &gates, Wires &wires) {
  Wire wire{.name = std::string{name}};
  if (auto wIter = wires.find(wire); wIter != wires.end())
    return wIter->val;
  Gate gate{.out = std::string{name}};
  auto gIter = gates.find(gate);
  assert(gIter != gates.end());
  auto leftVal = lookupVal(gIter->inA, gates, wires);
  auto rightVal = lookupVal(gIter->inB, gates, wires);
  auto res = gIter->op(leftVal, rightVal);
  wire.val = res;
  auto [_, inserted] = wires.insert(std::move(wire));
  assert(inserted);
  std::cout << *gIter << '\n';
  return res;
}

void solve2024day24b(std::istream &input) {
  namespace r4s = std::ranges;
  namespace v3s = r4s::views;

  Wires wires;

  r4s::for_each(r4s::istream_view<Wire>{input}, [&ws = wires](Wire const &w) {
    [[maybe_unused]] auto [_, inserted] = ws.insert(w);
    assert(inserted);
  });
  assert(not input.eof());
  input.clear();

  Gates gates;

  r4s::for_each(r4s::istream_view<Gate>{input}, [&gs = gates](Gate const &g) {
    [[maybe_unused]] auto [_, inserted] = gs.insert(g);
    assert(inserted);
  });
  assert(input.eof());

  Int number{};

  auto view = gates | v3s::reverse | v3s::take_while([](Gate const &g) {
                return g.out.starts_with('z');
              });

  r4s::for_each(view, [&](Gate const &g) {
    number <<= 1;
    if (lookupVal(g.out, gates, wires))
      number |= 1;
  });

  std::println("Puzzle answer is {}.", number);
}

} // namespace

int main(int const argc, char *const argv[]) {
  try {
    assert(argc == 2);
    std::ifstream ifs{argv[1]};
    assert(ifs);

    solve2024day24b(ifs);

    return EXIT_SUCCESS;
  } catch (std::bad_alloc const &) {
    std::fputs("Oops, out-of-memory\n", stderr);
  } catch (std::exception const &e) {
    std::println(stderr, "Some standard exception says: `{}'", e.what());
  }
  return EXIT_FAILURE;
}
