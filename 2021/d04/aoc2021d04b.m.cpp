#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <numeric>
#include <optional>
#include <ostream>
#include <ranges>
#include <span>
#include <sstream>
#include <string>
#include <vector>

#include <fmt/format.h>

constexpr int boardSize{5 * 5};

struct Board {
    std::array<int, boardSize> val;
    std::array<bool, boardSize> marked;
    int sumUnmarked;

    friend std::istream &operator>>(std::istream &in, Board &board) {
        for (auto &s: board.val) in >> s;
        if (in) board.marked.fill(false), board.sumUnmarked = std::accumulate(board.val.begin(), board.val.end(), 0);
        return in;
    }

    friend bool hasBoardWon(Board const &board) {
        using std::next;
        auto beg{board.marked.begin()};
        // check horizontal
        for (int i{}; i < boardSize - 5; i += 5)
            if (std::all_of(next(beg, i), next(beg, i + 5), [](bool bl) { return bl; }))
                return true;
        // check vertical
        for (int i{}; i != 5; ++i) {
            bool b{true};
            for (int j: {0, 5, 10, 15, 20})
                b = b && board.marked[i + j];
            if (b) return true;
        }
        return false;
    }
};

struct Score {
    int nth;
    int winNr;
    int sumUnmarked;
};

std::optional<Score> calcScore(Board &board, std::span<int const> draws) {
    int nth{};
    for (auto draw: draws) {
        auto it{std::ranges::find(board.val, draw)};
        if (it != board.val.end()) {
            board.sumUnmarked -= *it;
            board.marked[std::distance(board.val.begin(), it)] = true;
            if (hasBoardWon(board)) return Score{nth, draw, board.sumUnmarked};
        }
        ++nth;
    }
    return std::nullopt;
}

int main() {
    std::ifstream ifs{"../input.txt"};
    std::string line;
    std::getline(ifs, line);
    assert(ifs);
    std::istringstream iss{line};
    std::vector<int> draws;
    char comma;
    for (int draw; iss >> draw; iss >> comma)
        draws.push_back(draw);
    std::getline(ifs, line);
    assert(ifs && line.empty());
    std::optional<Score> lastScore;
    Board board;   // NOLINT
    int boardCnt{};
    while (ifs >> board)
        if (auto score{calcScore(board, draws)}; score)
            if (lastScore) [[likely]] {
                if (score->nth > lastScore->nth) lastScore = score;
            } else lastScore = score;
    if (lastScore) {
        int winNr{lastScore->winNr};
        int sum{lastScore->sumUnmarked};
        fmt::print("Nth {}, win nr {}, sum {}\nScore {}\n", lastScore->nth, winNr, sum, winNr * sum);
    } else fmt::print("No board won\n");

    // 2010 is too low
}

