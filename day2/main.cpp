#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	std::ifstream in{"input.txt"};
	unsigned cdigit = 6;

	struct Neighbor
	{
		unsigned up, right, down, left;
	};

	constexpr int A = 0xA, B = 0xB, C = 0xC, D = 0xD;

	std::vector<Neighbor> matches =
	{
		{0, 0, 3, 0}, // keypad 1
		{0, 3, 6, 0}, // keypad 2
		{1, 4, 7, 2}, // keypad 3
		{0, 0, 8, 3}, // keypad 4
		{0, 6, 0, 0}, // keypad 5
		{2, 7, A, 5}, // keypad 6
		{3, 8, B, 6}, // keypad 7
		{4, 9, C, 7}, // keypad 8
		{0, 0, 0, 8}, // keypad 9
		{6, B, 0, 0}, // keypad A
		{7, C, D, A}, // keypad B
		{8, 0, 0, B}, // keypad C
		{B, 0, 0, 0}  // keypad D
	};

	for (std::string raw; std::getline(in, raw);)
	{
		for (const char dir : raw)
		{
			switch (dir)
			{
			case 'U': if (matches[cdigit].up)    cdigit = matches[cdigit].up - 1;    break;
			case 'R': if (matches[cdigit].right) cdigit = matches[cdigit].right - 1; break;
			case 'D': if (matches[cdigit].down)  cdigit = matches[cdigit].down - 1;  break;
			case 'L': if (matches[cdigit].left)  cdigit = matches[cdigit].left - 1;  break;
			}
		}

		std::cout << std::hex << cdigit + 1;
	}
}
