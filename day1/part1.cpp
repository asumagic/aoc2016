#include "common.hpp"

#ifdef PART1

#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	if (argc != 2)
		return EXIT_FAILURE;

	std::ifstream path{argv[1]};

	Position cpos;
	Direction cdir = North;

	while (!path.eof())
	{
		char dir;
		int steps;

		path >> dir >> steps;
		path.ignore(2, ' ');

		rotate(cdir, dir == 'R');
		cpos = advance_by(cpos, cdir, steps);
	}

	std::cout << std::abs(cpos.x) + std::abs(cpos.y) << std::endl;
}

#endif
