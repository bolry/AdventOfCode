#include "common.h"

using namespace std;

static string const inc = "inc";
static string const lt = "<";
static string const eq = "==";
static string const gt = ">";
static string const le = "<=";
static string const ge = ">=";
static string const ne = "!=";

using Regs = unordered_map<string, int>;

void change(Regs& registers, int& max_seen, string const & reg_name, string const& op,
		int const the_change) {
	auto & reg_to_change = registers[reg_name];
	if (op == inc) {
		reg_to_change += the_change;
	} else { // dec
		reg_to_change -= the_change;
	}
	max_seen = max(reg_to_change, max_seen);
}

int main() {
	Regs regs;
	int max_seen = numeric_limits<int>::min();
	string reg_to_mod;
	string inc_or_dec;
	int steps;
	string ignore_if;
	string reg_to_qualify;
	string bool_op;
	int val;
	while (cin >> reg_to_mod >> inc_or_dec >> steps >> ignore_if >> reg_to_qualify >> bool_op >> val) {
		auto const & lookup_value = regs[reg_to_qualify];
		if ((bool_op == lt && lookup_value < val)
				|| (bool_op == le && lookup_value <= val)
				|| (bool_op == gt && lookup_value > val)
				|| (bool_op == ge && lookup_value >= val)
				|| (bool_op == eq && lookup_value == val)
				|| (bool_op == ne && lookup_value != val)) {
			change(regs, max_seen, reg_to_mod, inc_or_dec, steps);
		}
	}
	auto iter = max_element(begin(regs), end(regs),
			[](Regs::value_type const& a, Regs::value_type const& b) {
				return a.second < b.second;
			});
	cout << "Maximum register value is " << iter->second << "\n"
			"Highest register value seen during the process was " << max_seen << '\n';
	return 0;
}
