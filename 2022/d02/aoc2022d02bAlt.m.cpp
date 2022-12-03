int main() {
    std::ifstream ifs("../input.txt");
    assert(ifs);
    using namespace std::string_view_literals;
    int sum{};
    for (std::string line; std::getline(ifs, line);) {
        int s;
        if (line == "A X"sv) s = 3;
        else if (line == "A Y"sv) s = 4;
        else if (line == "A Z"sv) s = 8;
        else if (line == "B X"sv) s = 1;
        else if (line == "B Y"sv) s = 5;
        else if (line == "B Z"sv) s = 9;
        else if (line == "C X"sv) s = 2;
        else if (line == "C Y"sv) s = 6;
        else /*if (line == "C Z"sv)*/ s = 7;
        sum += s;
    }
    std::cout << "\nTotal score " << sum << '\n';

    return EXIT_SUCCESS;
}

/*

A X
A Y
A Z
B X
B Y
B Z
C X
C Y
C Z

 */
