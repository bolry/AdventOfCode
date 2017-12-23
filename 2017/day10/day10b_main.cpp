#include "common.h"

using namespace std;

int constexpr input_sz = 256;
vector<int> sparse_hash(input_sz);
auto const b = begin(sparse_hash);
auto const e = end(sparse_hash);
auto const rb = rbegin(sparse_hash);
auto const re = rend(sparse_hash);
int constexpr nr_ronds = 64;

void knot_hash_round(int &current_pos, int &skip_size,
                vector<int> const& lengths)
{
	for (int length : lengths) {
		rotate(b, b + current_pos, e); // left rotate
		reverse(b, b + length);
		rotate(rb, rb + current_pos, re); // right rotate
		current_pos += length + skip_size;
		current_pos %= input_sz;
		skip_size++;
	}
}

int main()
{
	iota(b, e, 0);
	string line;
	getline(cin, line);
	// trim leading and trailing whitespace
	line = regex_replace(line, regex("^ +(.*?) +$"), "$1");
	vector<int> lengths(line.size());
	copy(cbegin(line), cend(line), begin(lengths));
	lengths.insert(end(lengths), { 17, 31, 73, 47, 23 });
	int current_pos = 0;
	int skip_size = 0;
	for (int i = nr_ronds; i; i--) {
		knot_hash_round(current_pos, skip_size, lengths);
	}
	cout << hex << setfill('0');
	for (auto i = b; i != e; i += 16) {
		cout << setw(2) << accumulate(i, i + 16, 0, bit_xor<>());
	}
	cout << '\n';
}
