namespace {
constexpr auto prDebug = true;

using Int = long long;

} // namespace
int main() {
  [[maybe_unused]] constexpr char simp[]{
      R"END_DATA(.......S.......
...............
.......^.......
...............
......^.^......
...............
.....^.^.^.....
...............
....^.^...^....
...............
...^.^...^.^...
...............
..^...^.....^..
...............
.^.^.^.^.^...^.
...............
)END_DATA"};
  std::istringstream in{simp};
  // std::ifstream in{"../input.txt"};
  assert(in);
  using Row = std::string;
  Row row;
  std::getline(in, row); // top
  std::unordered_map<std::size_t, Int> beams{{row.find('S'), Int{1}}};
  assert(beams.begin()->first != Row::npos);
  decltype(beams) newBeams;
  while (std::getline(in, row)) {
    newBeams.clear();
    for (auto const &beam : beams) {
      if (row[beam.first] == '^') {
        newBeams[beam.first - 1u] += beam.second;
        newBeams[beam.first + 1u] += beam.second;
      } else {
        newBeams[beam.first] += beam.second;
      }
    }
    beams.swap(newBeams);
  }
  Int sum{};
  for (auto const &beam : beams) {
    sum += beam.second;
  }
  std::println("{}", sum);
}
