#define _GLIBCXX_DEBUG
#define _GLIBCXX_DEBUG_PEDANTIC
#define _LIBCPP_DEBUG 1

#include <cassert>
#include <cctype>
#include <charconv>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace {
constexpr int kBase = 36;

enum Op {
  And,
  Or,
  Not,
  Lshift,
  Rshift,
  Value,
  Variable,
};

using U16 = std::uint16_t;

struct Id {
  int id;
};

struct Val {
  U16 val;
};

struct Tuple {
  Op op;
  std::variant<Id, Val> m0;
  std::variant<Id, Val> m1;
};
using Vec = std::vector<Tuple>;

} // namespace

int main() {
  using namespace std::string_view_literals;

  std::ifstream in("../input2.txt");
  Vec wiring;
  wiring.resize(1 + std::invoke([] {
                  constexpr char str[] = "zz";
                  std::size_t result{};
                  std::from_chars(str, str + 2, result, kBase);
                  return result;
                }));
  std::string m0, m1, m2, m3, m4;
  while (in >> m0 >> m1 >> m2) {
    constexpr auto kArrow = "->"sv;
    if (m1 == kArrow) // "123 -> a" or "b -> a"
    {
      std::size_t const idx = std::stoul(m2, 0, kBase);
      if (std::isalpha(static_cast<unsigned char>(m0.front()))) {
        wiring[idx].op = Op::Variable;
        std::get<Id>(wiring[idx].m0).id = std::stoi(m0, 0, kBase);
      } else {
        wiring[idx].op  = Op::Value;
        std::get<Val>(wiring[idx].m0).val =
            static_cast<U16>(std::stoul(m0, 0, kBase));
      }
    } else if (m0 == "NOT"sv) // "NOT a -> b"
    {
      in >> m3;
      assert(in && (m2 == kArrow));
      std::size_t const idx = std::stoul(m3, 0, kBase);
      wiring[idx].op = Op::Not;
      std::get<Id>(wiring[idx].m0).id = std::stoi(m1, 0, kBase);
    } else if (m1 == "AND"sv || m1 == "OR"sv) {
      in >> m3 >> m4;
      assert(in && (m3 == kArrow));
      std::size_t const idx = std::stoul(m4, 0, kBase);
      if (m1 == "AND"sv)
        wiring[idx].op = Op::And;
      else
        wiring[idx].op = Op::Or;
      if (std::isalpha(static_cast<unsigned char>(m0.front()))) {
        std::get<Id>(wiring[idx].m0).id = std::stoi(m0, 0, kBase);
      } else {
        std::get<Val>(wiring[idx].m0).val =
            static_cast<U16>(std::stoul(m0, 0, kBase));
      }
      std::get<Id>(wiring[idx].m1).id = std::stoi(m2, 0, kBase);
    } else if (m1.ends_with("SHIFT"sv)) {
      in >> m3 >> m4;
      assert(in && (m3 == kArrow));
      std::size_t const idx = std::stoul(m4, 0, kBase);
      if (m1 == "LSHIFT"sv)
        wiring[idx].op = Op::Lshift;
      else
        wiring[idx].op = Op::Rshift;
      std::get<Id>(wiring[idx].m0).id = std::stoi(m0, 0, kBase);
      std::get<Val>(wiring[idx].m1).val =
          static_cast<U16>(std::stoul(m2, 0, kBase));
    } else {
      assert(false);
    }
  }
}
