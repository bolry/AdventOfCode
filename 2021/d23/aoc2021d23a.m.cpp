// #############
// #...........#
// ###D#A#C#C###
//   #D#A#B#B#
//   #########
// 10*1
// #############
// #AA.........#
// ###D#.#C#C###
//   #D#.#B#B#
//   #########
// 2*100
// #############
// #AA.....C...#
// ###D#.#.#C###
//   #D#.#B#B#
//   #########
// 6*10
// #############
// #AA.....C...#
// ###D#.#.#C###
//   #D#b#.#B#
//   #########
// 7*100
// #############
// #AA.........#
// ###D#.#c#.###
//   #D#b#c#B#
//   #########
// 7*10
// #############
// #AA.........#
// ###D#b#c#.###
//   #D#b#c#.#
//   #########
// 18*1000
// #############
// #AA.........#
// ###.#b#c#d###
//   #.#b#c#d#
//   #########
// 6*1
// #############
// #...........#
// ###a#b#c#d###
//   #a#b#c#d#
//   #########



// #############
// #...........#
// ###A#B#C#D###
//   #A#B#C#D#
//   #########

enum Amphipods : char {
    Amber = 'A', Bronze = 'B', Copper = 'C', Desert = 'D',
};

struct SA {
};

struct Burrow {
};

using fmt::print;

int main() {
    print("{}\n", 10*1 + 2*100 +6*10 + 7*100 + 7*10+18*1000+6*1 );
}

// 12701 too low
