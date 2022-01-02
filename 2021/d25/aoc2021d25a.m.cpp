using fmt::print;
using namespace std::literals::string_view_literals;

void pr(std::string_view map, int width, std::string_view prefix) {
    if (!prefix.empty()) print("\n{}\n", prefix);
    for (; !map.empty(); map.remove_prefix(width)) print("{:.{}}\n", map, width);
}

std::string nextMap;

bool moveEast(std::string &map, int width) {
    bool moved{};
    nextMap = map;
    int w{};
    for (int i{}, e = ssize(map); i != e; ++i) {
        int nextI{i + 1};
        ++w;
        if (w == width) {
            w = 0;
            nextI -= width;
        }
        if (map[i] == '>' && map[nextI] == '.') {
            moved = true;
            std::ranges::swap(nextMap[i], nextMap[nextI]);
        }
    }
    std::ranges::swap(map, nextMap);
    return moved;
}

bool moveSouth(std::string &map, int width, int height) {
    bool moved{};
    nextMap = map;
    for (int i{}, e = ssize(map); i != e; ++i) {
        int nextI{i + width};
        if (nextI >= e) nextI -= e;
        if (map[i] == 'v' && map[nextI] == '.') {
            moved = true;
            std::ranges::swap(nextMap[i], nextMap[nextI]);
        }
    }
    std::ranges::swap(nextMap, map);
    return moved;
}

int main(int argc, char *argv[]) {
    assert(argc == 2 && "missing argument");
    std::string map;
    map.reserve(std::filesystem::file_size(argv[1]));
    std::ifstream ifs{argv[1]};
    ifs >> map;
    int width = gsl::narrow_cast<int>(ssize(map));
    print("width {} ", width);
    std::remove_copy_if(std::istreambuf_iterator<char>{ifs}, {}, std::back_inserter(map),
                        [](unsigned char c) { return std::isspace(c); });
    ifs.close();
    map.shrink_to_fit();
    int height = gsl::narrow_cast<int>(ssize(map)) / width;
    print("height {}\n", height);
    assert(width * height == ssize(map));
    pr(map, width, "Initial state:"sv);
    int step{};
    for (;;) {
        bool moved = moveEast(map, width);
        if (!moveSouth(map, width, height) && !moved) break;
        ++step;
        // pr(map, width, fmt::format("After {} steps:", step));
    }
    pr(map, width, fmt::format("After {} steps:", step));
    print("\nStep {}\n", ++step);
}
