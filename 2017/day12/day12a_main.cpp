#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>

using namespace std;

int main()
{
	unordered_map<int, set<int>> connections;
	for (string line; getline(cin, line);) {
		istringstream iss(line);
		int p;
		string ignore_arrow;
		iss >> p >> ignore_arrow;
		char ignore_comma;
		auto& p_mapped = connections[p];
		for (int p2; iss >> p2; iss >> ignore_comma) {
			p_mapped.insert(p2);
		}
	}
	set<int> zeros { 0 };

	for (bool try_again = true; try_again;) {
		try_again = false;
		for (auto i = begin(zeros), e = end(zeros); i != e; ++i) {
			auto something_added = false;
			for (auto others : connections[*i]) {
				bool inserted;
				tie(ignore, inserted) = zeros.insert(others);
				if (inserted) {
					something_added = true;
				}
			}
			if (something_added) {
				try_again = true;
				break;
			}
		}
	}

	cout << "Nr zero associated programs " << zeros.size() << '\n';
}
