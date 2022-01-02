using fmt::print;

bool isLowPoint(std::string_view map, int width, int height, int idx) {
    auto d{std::div(idx, width)};
    int x{d.rem};
    int y{d.quot};
    // up
    if (y != 0 && map[idx] >= map[idx - width]) return false;
    // right
    if (x != width - 1 && map[idx] >= map[idx + 1]) return false;
    // down
    if (y != height - 1 && map[idx] >= map[idx + width]) return false;
    // left
    if (x != 0 && map[idx] >= map[idx - 1]) return false;

    return true;
}

int basinSize(std::string &map, int width, int height, int idx) {
    int sz{};
    if (map[idx] == '9') return sz;
    auto oldValue{std::exchange(map[idx], '\0')};
    ++sz;
    auto d{std::div(idx, width)};
    int x{d.rem};
    int y{d.quot};
    // up
    if (y != 0 && oldValue < map[idx - width]) sz += basinSize(map, width, height, idx - width);
    // right
    if (x != width - 1 && oldValue < map[idx + 1]) sz += basinSize(map, width, height, idx + 1);
    // down
    if (y != height - 1 && oldValue < map[idx + width]) sz += basinSize(map, width, height, idx + width);
    // left
    if (x != 0 && oldValue < map[idx - 1]) sz += basinSize(map, width, height, idx - 1);

    return sz;
}

void findBasinSizes(std::unordered_map<int, int> &basins, std::string &map, int width, int height) {
    for (auto &[id, sz]: basins) sz = basinSize(map, width, height, id);
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
    std::unordered_map<int, int> basins;
    for (int i{}, e(map.size()); i < e; ++i)
        if (isLowPoint(map, width, height, i))
            basins[i];
    print("Nr of basins {}\n", basins.size());
    findBasinSizes(basins, map, width, height);
    std::vector<int> sizes;
    sizes.reserve(basins.size());
    for (auto &[id, sz]: basins) sizes.push_back(sz);
    std::ranges::nth_element(sizes, std::next(sizes.begin(), 3), std::ranges::greater{});
    auto mul3{std::accumulate(sizes.begin(), std::next(sizes.begin(), 3), 1, std::multiplies<int>{})};
    print("Multiply answer {}\n", mul3);
}
