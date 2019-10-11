#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

namespace {

//char const input[] = "464 players; last marble is worth 70918 points";
//char const input[] = "9 players; last marble is worth 25 points";

struct Result {
  int high_score;
};

struct GameState {
  std::vector<int> player_scores;
  int next_player;
  std::vector<int> circle;
  int current_marble_offset;
  int round;
};

GameState make_gs(int const players, int const last_marbel){
  GameState gs;
  gs.player_scores.resize(players);
  gs.next_player = 0;
  gs.circle.reserve(last_marbel + 1);
  gs.circle.resize(1);
  gs.current_marble_offset = 0;
  gs.round = 0;
  return gs;
}

void print(GameState const& gs){
  if(gs.next_player == 0) std::cout << "[-]"; else std::cout << '[' << gs.next_player << ']';
  for(int i = 0; i < gs.current_marble_offset; i++){
    std::cout << ' ' <<gs.circle[i];
  }
  std::cout << " (" << gs.circle[gs.current_marble_offset] << ')';
  for(int i = gs.current_marble_offset + 1 ; i < gs.circle.size(); i++){
    std::cout << ' ' << gs.circle[i];
  }
  std::cout <<'\n';
}

int scores(std::vector<int> const& players){
//  std::copy(players.begin(), players.end(), std::ostream_iterator<int>(std::cout, " "));
//  std::cout << '\n';
  return *std::max_element(players.begin(), players.end());
}

void next_step(GameState& gs){
  gs.round++;
  gs.next_player++;
  if(gs.next_player > gs.player_scores.size())
  {
    gs.next_player = 1;
  }
  if(gs.round % 23){
    int noffset = gs.current_marble_offset + 2;
    if(noffset > gs.circle.size()){
      noffset = 1;
    }
    gs.circle.insert(gs.circle.begin() + noffset, gs.round);
    gs.current_marble_offset = noffset;
  }
  else{
    gs.player_scores[gs.next_player-1] = gs.round;
    int next_marble = gs.current_marble_offset - 7;
    if(next_marble < 0) next_marble = static_cast<int>(gs.circle.size()) + next_marble;
    gs.player_scores[gs.next_player-1] += gs.circle[next_marble];
    gs.circle.erase((gs.circle.begin() + next_marble));
    gs.current_marble_offset = next_marble;
  }
}

Result simulate(int const players, int const last_marble) {
  std::cout << players << " players; last marbel is worth " << last_marble;
  GameState gs = make_gs(players, last_marble);
  for(int i = 0; i <= last_marble ; ++i)
  {
  //  print(gs);
    next_step(gs);
  }
  return { scores(gs.player_scores)};
}

}  // close anonymous namespace

int main() {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  Result const result = simulate(9, 25);
  std::cout << ": high score is " << result.high_score << '\n';
  return EXIT_SUCCESS;
}
