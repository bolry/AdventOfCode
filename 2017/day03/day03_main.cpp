#include <iostream>
#include <vector>

//constexpr int input = 277678;

int constexpr input = 4;

enum class Direction {
	right, up, left, down
};

int main() {
	Direction direction = Direction::right;
	int width = 0;
	int x_offset = 0;
	int y_offset = 0;
	int i = 1;
	int running_total = 0;
	while (i <= input) {
		switch (direction) {
		case Direction::right:
			++x_offset;
			if(x_offset > width){
				++width;
				direction = Direction::up;
			}
			break;
		case Direction::up:
			++y_offset;
			if(y_offset == width){
				direction = Direction::left;
			}
			break;
		case Direction::left:
			--x_offset;
			if(x_offset == -width){
				direction = Direction::down;
			}
			break;
		case Direction::down:
			--y_offset;
			if(y_offset == -width)
			{
				direction = Direction::right;
			}
			break;
		}
		i += running_total;
		running_total = i;
	}
	std::cout << "Next number larger than " << input << " is "
			<< i << '\n';
}
