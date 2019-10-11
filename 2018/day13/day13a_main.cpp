#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
typedef std::array<char, 13> Row;
typedef std::array<Row, 6> Matrix;
enum class Dir : char { up = '^', down = 'v', left = '<', right = '>' };
enum class Turn { left, straight, right };

Turn &operator++(Turn &t) {
  switch (t) {
    case Turn::left: return t = Turn::straight;
    case Turn::straight: return t = Turn::right;
    case Turn::right: return t = Turn::left;
  }
}

Turn operator++(Turn &t, int) {
  Turn t2 = t;
  return ++t2;
}
struct Cart {
  int x;
  int y;
  Dir face;
  Turn next_turn;
};
}  // close anonymous namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2)
    throw std::runtime_error("Need file name argument");
  std::ifstream in_file(argv[1]);
  if (!in_file)
    throw std::runtime_error("Unable to open file " + std::string(argv[1]));
  Matrix map;
  for (int y = 0; in_file && y < static_cast<int>(map[0].size()); y++) {
    in_file.read(map[y].data(), map[y].size());
    in_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  for (auto const &r : map) {
    std::cout << 'L';
    std::cout.write(r.data(), r.size()) << "R\n";
  }
  Turn t;
  t++;
  ++t;
  return EXIT_SUCCESS;
}
