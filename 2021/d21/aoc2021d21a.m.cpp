// Player 1 starting position: 10
// Player 2 starting position: 1

using fmt::print;

struct Pawn {
    int score{};
    int position;

    void move(int dist) {
//        print("On pos {} ", position);
        position += dist;
        position = (position - 1) % 10 + 1;
        score += position;
  //      print(" next pos is {}\n", position);
    }
};

struct Dice {
    int nrSides;
    int nextNr{1};
    int nrRolls{};

    int roll() {
        ++nrRolls;
        int res = nextNr;
        ++nextNr;
        if (nextNr > nrSides) nextNr = 1;
        return res;
    }

    int roll(int x) {
        int sum{};
        for (int i{}; i < x; ++i) sum += roll();
        return sum;
    }
};

bool playRound(Pawn &player, Dice &dice) {
    int sumRolls = dice.roll(3);
    player.move(sumRolls);
  //  print("Player rolls {} total score {}\n", sumRolls, player.score);
    return player.score >= 1000;
}

int main() {
    Dice dice{.nrSides=100};
    Pawn player1{.position=10};
    Pawn player2{.position=1};

    for (;;) {
        if (playRound(player1, dice)) break;
        if (playRound(player2, dice)) break;
    }
    int loserScore = player1.score >= 1000 ? player2.score : player1.score;
    fmt::print("Loser {} rolls {}\nEnd score: {}\n", loserScore, dice.nrRolls, loserScore * dice.nrRolls);
}
// 1190808 is wrong