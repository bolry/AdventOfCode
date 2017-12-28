#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <map>
using namespace std;

using Banks = vector<int>;

int Count(Banks& ar_banks) {
	auto cycle = 0;
	auto b = begin(ar_banks);
	auto e = end(ar_banks);
	map<Banks, int> history;
	while (++history[ar_banks] == 1) {
		++cycle;
		auto iter = max_element(b, e);
		auto val = *iter;
		*iter = 0;
		for (; val != 0; --val) {
			++iter;
			if (iter == e) {
				iter = b;
			}
			*iter += 1;
		}
	}
	return cycle;
}

int main() {
	Banks banks;
	copy(istream_iterator<int>(cin), istream_iterator<int>(),
			back_inserter(banks));
	(void) Count(banks);
	auto cycle = Count(banks);
	cout << "Nr of recycles before repeat is " << cycle << '\n';
}
