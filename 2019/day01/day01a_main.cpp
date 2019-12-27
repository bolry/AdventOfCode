#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>

namespace {
struct Module {
  int mass;

  [[nodiscard]] int fuelNeeded() const noexcept { return mass / 3 - 2; }

  friend std::istream &operator>>(std::istream &is, Module &module) {
    is >> module.mass;
    return is;
  }
};

} // namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::ios_base::badbit | std::ios_base::eofbit |
                       std::ios_base::failbit);
  if (argc < 2) {
    throw std::runtime_error("need filename argument");
  }
  std::ifstream inFile(argv[1]);
  if (!inFile) {
    throw std::runtime_error("problem opening file " + std::string(argv[1]));
  }
  std::istream_iterator<Module> moduleReader(inFile);
  std::istream_iterator<Module> const moduleReaderEof;
  std::cout << "Total amount of fuel needed is "
            << std::accumulate(moduleReader, moduleReaderEof, 0,
                               [](int totalSoFar, auto module) {
                                 return totalSoFar + module.fuelNeeded();
                               })
            << '\n'
            << std::flush;
  return EXIT_SUCCESS;
}
