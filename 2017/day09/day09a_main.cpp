#include <iostream>

constexpr char cancel = '!';
constexpr char garbage_start = '<';
constexpr char garbage_end = '>';
constexpr char group_start = '{';
constexpr char group_end = '}';

int main()
{
	char ch;
	int group_score = 0;
	int group_level = 0;
	bool in_garbage = false;
	bool ignore_next = false;
	while (std::cin >> ch)
		if (ignore_next)
			ignore_next = false;
		else if (in_garbage)
			switch (ch) {
			case garbage_end:
				in_garbage = false;
				break;
			case cancel:
				ignore_next = true;
				break;
			}
		else
			switch (ch) {
			case group_start:
				group_score += ++group_level;
				break;
			case group_end:
				--group_level;
				break;
			case garbage_start:
				in_garbage = true;
				break;
			}
	std::cout << "Group score " << group_score << '\n';
}
