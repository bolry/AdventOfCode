#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <new>
#include <numeric>
#include <string>
#include <vector>

namespace {

typedef std::vector<int> Row;

struct Claim {
  int id;
  int left_offset;
  int top_offset;
  int width;
  int height;
};

std::istream &operator>>(std::istream &in, Claim &claim) {
  char hash, comma, colon, x;
  std::string at;
  return in >> hash >> claim.id >> at >> claim.left_offset >> comma >> claim.top_offset >> colon >> claim.width >> x
            >> claim.height;
}

void cover_claim(Claim const &claim, std::vector<Row> &fabric) {
  int const col_first = claim.left_offset;
  int const col_last = col_first + claim.width;
  for (int i = claim.top_offset; i < claim.top_offset + claim.height; i++) {
    auto row_begin = fabric.at(i).begin();
    std::for_each(row_begin + col_first, row_begin + col_last, [](int &n) { n++; });
  }
}

}

int main(int argc, char *argv[])
try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("Need input data filename\n");
  std::ifstream claim_file(argv[1]);
  if (!claim_file) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
  std::istream_iterator<Claim> claim_reader(claim_file);
  std::istream_iterator<Claim> claim_reader_EOF;
  std::vector<Claim> claims;
  std::copy(claim_reader, claim_reader_EOF, std::back_inserter(claims));
  auto max_width_claim = std::max_element(claims.begin(), claims.end(), [](Claim const &a, Claim const &b) {
    return (a.left_offset + a.width) < (b.left_offset + b.width);
  });
  std::cout << "line nr:" << std::distance(claims.begin(), max_width_claim) + 1 << '\n';
  std::cout << "Big width (leftoffset):" << max_width_claim->left_offset << " (width):" << max_width_claim->width
            << '\n';
  auto max_height_claim = std::max_element(claims.begin(), claims.end(), [](Claim const &a, Claim const &b) {
    return (a.top_offset + a.height) < (b.top_offset + b.height);
  });
  std::cout << "line nr:" << std::distance(claims.begin(), max_height_claim) + 1 << '\n';
  std::cout << "Big height (top_offset):" << max_height_claim->top_offset << " (height):" << max_height_claim->height
            << '\n';
  int const fabric_width = max_width_claim->left_offset + max_width_claim->width;
  int const fabric_height = max_height_claim->top_offset + max_height_claim->height;
  std::cout << "fabric width: " << fabric_width << " fabric height: " << fabric_height << '\n';
  std::vector<Row> fabric(fabric_height, Row(fabric_width));
  for (Claim const &claim : claims) {
    cover_claim(claim, fabric);
  }
  int claimed_squares = 0;
  for (Row const &claim : fabric) {
    claimed_squares += std::accumulate(claim.begin(), claim.end(), 0, [](int acc, int val) {
      return acc + (val >= 2);
    });
  }
  std::cout << "Squares claimed by two or more: " << claimed_squares << '\n' << std::flush;
  return EXIT_SUCCESS;
}
catch (std::bad_alloc const &) {
  std::fputs("Sorry, out-of-memory\n", stderr);
  std::fflush(stderr);
  return EXIT_FAILURE;
}
catch (std::exception const &x) {
  std::cerr << x.what() << '\n' << std::flush;
  return EXIT_FAILURE;
}
#if 0
catch (...) {
    std::cerr << "Unexpected unhandled error\n" << std::flush;
    return EXIT_FAILURE;
}
#endif  // 0
