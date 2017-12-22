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

void change(Regs& regs, string const & reg, string const& op, int const val) {
	if (op == inc) {
		regs[reg] += val;
	} else { // dec
		regs[reg] -= val;
	}
}

int main() {
	Regs regs;
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
			change(regs, reg_to_mod, inc_or_dec, steps);
		}
	}
	auto iter = max_element(begin(regs), end(regs),
			[](Regs::value_type const& a, Regs::value_type const& b) {
				return a.second < b.second;
			});
	cout << "Maximum register value is " << iter->second << '\n';
	return 0;
}
