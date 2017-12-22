#include "common.h"

using namespace std;

int main() {
	using Children = unordered_map<string, string>;
	Children children;
	string line;
	string parent;
	string ignore_weight;
	string arrow;
	string child;
	while (getline(cin, line)) {
		istringstream iss(line);
		iss >> parent >> ignore_weight;
		children[parent];
		if (iss >> arrow) {
			while (iss >> child) {
				if (child.back() == ',') {
					child.pop_back();
				}
				children[child] = parent;
			}
		}
	}
	auto grand_iter = find_if(begin(children), end(children),
			[](Children::value_type const & c) {
				return c.second.empty();
			});
	cout << "Grand program is " << grand_iter->first << '\n';
}
