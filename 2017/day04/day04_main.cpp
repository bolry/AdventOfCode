#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>

using namespace std;

int main() {
	int valid = 0;
	string line;
	while (std::getline(std::cin, line)) {
		map<string, int> vs;
		istringstream iss(line);
		bool good = true;
		for (auto iter = istream_iterator<string>(iss);
				iter != istream_iterator<string>(); ++iter) {
			string word(*iter);
			sort(begin(word), end(word));
			if (vs[word]++) {
				good = false;
				break;
			}
		}
		if (good) {
			++valid;
		}
	}
	cout << "Nr valid passphrases are " << valid << '\n';
}
