#include "common.h"

struct Name {
	std::string name;
};

namespace std{
 template<> struct hash<Name>{
	 typedef Name argument_type;
	 typedef std::size_t result_type;
	 result_type operator()(argument_type const & n) const noexcept{
		 return std::hash<std::string>{}(n.name);
	 }
 }
}

using namespace std;

bool operator==(const Name& lhs, const Name& rhs){
	return lhs.name == rhs.name;
}

using Children = set<Name>;
using Holder = unordered_map<Name, Children>;

void find_better_root(Name const& name, Holder const& holder, Name* root) {
	for (auto const& p : holder) {
//		if (p.second.name.count(name.name)) {
//			*root.name = p.first;
//			return;
//		}
	}
}

int main() {
	Name root;
	string line;
	Holder hmm;
	while (getline(cin, line)) {
		istringstream iss(line);
		Name name;
		int weight;
		char ch;
		iss >> name >> ch >> weight >> ch;
		string arrow;
		if (iss >> arrow) {
			Children aboves;
			for (Name above; iss >> above;) {
				if (above.back() == ',') {
					above.erase(end(above) - 1);
				}
				hmm.erase(above);
				aboves.insert(above);
			}
			find_better_root(name, hmm, &root);
			hmm.insert(make_pair(name, aboves));
			if (root.empty()) {
				root = name;
			}
		}
	}
	while(hmm.size() > 1U){
		for(auto iter = hmm.begin(); iter != hmm.end(); ++iter){
			bool erased = false;
			for( auto child : iter->second){
				erased = erased || (hmm.erase(child) != 0U);
			}
			if(erased){
				break;
			}
		}
	}
	cout << "Root program is `" << hmm.begin()->first << "'\n";
}
