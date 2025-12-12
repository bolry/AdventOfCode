namespace {
constexpr auto prDebug = true;

using Int = int;
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
  Int splits{};
  using Row = std::string;
  Row row;
  std::getline(in, row); // top
  std::unordered_set beams{row.find('S')};
  assert(*beams.begin() != Row::npos);
  decltype(beams) newBeams;
  while (std::getline(in, row)) {
    newBeams.clear();
    for (auto beam : beams) {
      if (row[beam] == '^') {
        newBeams.insert(beam - 1u);
        newBeams.insert(beam + 1u);
        ++splits;
      } else {
        newBeams.insert(beam);
      }
    }
    beams.swap(newBeams);
  }
  std::println("{}", splits);
}
