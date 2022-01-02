using fmt::print;

int main() {
  std::ifstream ifs{"../input.txt"};
  assert(ifs && "cant open file");
  std::string line;
  std::getline(ifs, line);
  assert(ifs && "unable to read file");
  print("Original polymer template: `{}'\n", line);

  std::unordered_map<std::string, char> dict;
  {
    std::string key, arrow;
    char ch;
    while (ifs >> key >> arrow >> ch)
      dict[key] = ch;
    assert(arrow == "->");
  }
  ifs.close();

  std::string newLine;
  for (int i{}; i < 10;) {
    ++i;
    newLine.clear();
    newLine.reserve(line.size() * 2);
    for (int j = 1; j < line.size(); ++j) {
      newLine.push_back(line[j - 1]);
      std::string key{line[j - 1], line[j]};
      auto iter = dict.find(key);
      if (iter != dict.end()) {
        newLine.push_back(iter->second);
      }
    }
    newLine.push_back(line.back());
    newLine.swap(line);
    // print("After step {}: {}\n", i, line);
  }

  std::unordered_map<char, int> counter;
  for (char c : line)
    ++counter[c];

  auto [small, big] = std::minmax_element(
      counter.begin(), counter.end(),
      [](auto const &a, auto const &b) { return a.second < b.second; });

  print("Small `{}` occurs {} times\n"
        "Big `{}' occurs {} times\n",
        small->first, small->second, big->first, big->second);

  print("Answer {}\n", big->second - small->second);
}
