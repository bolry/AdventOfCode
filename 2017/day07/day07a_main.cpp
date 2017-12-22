#include "common.h"

using namespace std;

int main() {
	// true if child has parent
	using Children = unordered_map<string, bool>;
	Children children;
	string line;
	string parent;
	string ignore_weight;
	string ignore_arrow;
	string child;
	while (getline(cin, line)) {
		istringstream iss(line);
		iss >> parent >> ignore_weight;
		children[parent]; // defaults to false if new instance
		if (iss >> ignore_arrow) {
			while (iss >> child) {
				if (child.back() == ',') {
					child.pop_back();
				}
				children[child] = true;
			}
		}
	}
	auto grand_iter = find_if(begin(children), end(children),
			[](Children::value_type const & c) {
				return c.second == false;
			});
	cout << "Grand program is " << grand_iter->first << '\n';
}
