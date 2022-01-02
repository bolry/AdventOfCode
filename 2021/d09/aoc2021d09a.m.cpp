using fmt::print;

int smallestVal(std::string_view map, int width, int height, int idx) {
    auto d{std::div(idx, width)};
    int x{d.rem};
    int y{d.quot};
    // up
    if (y != 0 && map[idx] >= map[idx - width]) return 0;
    // right
    if (x != width - 1 && map[idx] >= map[idx + 1]) return 0;
    // down
    if (y != height - 1 && map[idx] >= map[idx + width]) return 0;
    // left
    if (x != 0 && map[idx] >= map[idx - 1]) return 0;

    return map[idx] - '0' + 1;
}

int main() {
    std::ifstream ifs{"../input.txt"};
    assert(ifs && "Cant open file");
    std::string map;
    std::getline(ifs, map);
    auto const width{map.size()};
    std::string line;
    while (std::getline(ifs, line)) map += line;
    auto const height{map.size() / width};
    print("w: {} h: {}\n", width, height);
    int sum{};
    for (int i{}, e(map.size()); i < e; ++i) sum += smallestVal(map, width, height, i);
    print("Points {}\n", sum);
}
