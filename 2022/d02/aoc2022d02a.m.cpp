
namespace {
    enum Shape {
        Rock = 1, Paper, Scissors,
    };

    constexpr Shape isFig(char ch) noexcept {
        if (ch == 'A' or ch == 'X') return Rock;
        else if (ch == 'B' or ch == 'Y') return Paper;
        else /*if (ch == 'C' or ch == 'Z')*/ return Scissors;
    }

    constexpr int myScore(char me, char other) noexcept {
        auto const myFig = isFig(me);
        auto const otherFig = isFig(other);
        // tie
        if (myFig == otherFig) return 3 + myFig;
        // I win
        else if ((myFig == Rock and otherFig == Scissors) or
                 (myFig == Scissors and otherFig == Paper) or
                 (myFig == Paper and otherFig == Rock))
            return 6 + myFig;
        // I lose
        else return myFig;
    }
}

int main() {
    std::ifstream ifs("../input.txt");
    assert(ifs);

    int sum{};
    for (std::string line; std::getline(ifs, line);) {
        assert(line.size() == 3);
        int s = myScore(line[2], line[0]);
        std::cout << '`' << line << "' score: " << s << '\n';
        sum+=s;
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
