#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>

using namespace std;

int main()
{
	using Map =
	unordered_map<int, set<int>>;
	Map connections;
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

	set<int> untried_progs;
	transform(begin(connections), end(connections),
	                inserter(untried_progs, begin(untried_progs)),
	                [](Map::value_type const& m) {return m.first;});

	int nr_of_groups = 0;

	while (!untried_progs.empty()) {
		nr_of_groups++;
		set<int> progs_in_grp{*untried_progs.begin()};
		untried_progs.erase(*progs_in_grp.begin());
		for (bool try_again = true; try_again;) {
			try_again = false;
			for (auto i = begin(progs_in_grp), e = end(
			                progs_in_grp); i != e; ++i) {
				auto something_added = false;
				for (auto others : connections[*i]) {
					bool inserted;
					tie(ignore, inserted) =
					                progs_in_grp.insert(
					                                others);
					if (inserted) {
						untried_progs.erase(others);
						something_added = true;
					}
				}
				if (something_added) {
					try_again = true;
					break;
				}
			}
		}
		cout << "Programs in group " << progs_in_grp.size() << '\n';
	}
	cout << "Total nr of groups " << nr_of_groups << '\n';
}
