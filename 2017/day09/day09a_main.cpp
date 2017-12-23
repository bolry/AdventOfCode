#include <iostream>

char const cancel = '!';
char const garbage_start = '<';
char const garbage_end = '>';
char const group_start = '{';
char const group_end = '}';

int main()
{
	bool ignore_next = false;
	bool in_garbage = false;
	char ch;
	int garbage_count = 0;
	int group_level = 0;
	int group_score = 0;
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
			default:
				garbage_count++;
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
	std::cout << "Group score " << group_score << "\n"
			"Garbage count " << garbage_count << '\n';
}
