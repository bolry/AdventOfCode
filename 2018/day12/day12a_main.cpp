#include <algorithm>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>

namespace {
typedef std::map<std::string, char> Map;

int zero_offset = 0;

std::string next_gen(std::string const& pots, Map const &notes) {
  std::string const ref_pots = ".." + pots + "..";
  std::string new_pots(ref_pots.size(), '.');
  for(int i = 0; i < static_cast<int>(ref_pots.size()) - 4; ++i){
    new_pots[i+2] = notes.find(ref_pots.substr(i, 5))->second;
  }
  int const offset = static_cast<int>(new_pots.find('#'));
  new_pots.erase(new_pots.begin(), new_pots.begin() + offset);
  new_pots.resize(new_pots.rfind('#')+1);
  zero_offset -= offset - 2;
  return new_pots;
}

int sum(int const zero_at, std::string const&pots){
  int res = 0;
  for(int i = 0, e = pots.size(); i < e; ++i)
    if(pots[i]== '#')
      res += i - zero_at;
  return res;
}

}  // close anonymous namespace

int main(int argc, char *argv[]) {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2)
    throw std::runtime_error("Need filename argument");
  std::ifstream in_file(argv[1]);
  if (!in_file)
    throw std::runtime_error("unable to open file " + std::string(argv[1]));
  std::string line;
  std::string pots;
  in_file >> line >> line >> pots;
  Map notes;
  std::string note, arrow;
  char value;
  while (in_file >> note >> arrow >> value)
    notes[note] = value;
  int i;
  for (i = 0; i < 20; i++) {
    std::cout << i << ": " << pots << '\n';
    pots = next_gen(pots, notes);
  }
  std::cout << i << ": " << pots << '\n';
  std::cout << zero_offset << '\n';
  std::cout << sum(zero_offset, pots) << '\n';
  return EXIT_SUCCESS;
}
