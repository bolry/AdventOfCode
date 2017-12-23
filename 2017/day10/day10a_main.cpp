#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
	int const input_sz = 256;
	vector<int> v(input_sz);
	auto const b = begin(v);
	auto const e = end(v);
	auto const rb = rbegin(v);
	auto const re = rend(v);
	iota(b, e, 0);
	int current_pos = 0;
	int skip_size = 0;
	for (int length; cin >> length; cin.ignore(1)) { // remove trailing comma ','
		rotate(b, b + current_pos, e); // left rotate
		reverse(b, b + length);
		rotate(rb, rb + current_pos, re); // right rotate
		current_pos += length + skip_size;
		current_pos %= input_sz;
		skip_size++;
	}
	cout << "Answer is " << v[0] * v[1] << '\n';
}
