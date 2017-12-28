#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>

using namespace std;

int main() {
	vector<int> v;
	copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(v));
	copy(begin(v), end(v), ostream_iterator<int>(cout, ", "));
	cout << '\n';
	int const len = v.size();
	int pc = 0;
	int steps = 0;
	while (0 <= pc && pc < len) {
		++steps;
		int const jump = v[pc];
		if (jump >= 3) {
			v[pc]--;
		} else {
			v[pc]++;
		}
		pc += jump;
	}
	cout << "Nr of steps " << steps << '\n';
}
