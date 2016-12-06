#include "common.hpp"

#ifdef PART2

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char *argv[])
{
	if (argc != 2)
		return EXIT_FAILURE;

	std::ifstream path{argv[1]};

	std::vector<Position> stop_points;
	bool has_visited_twice = false;
	Position visited_twice;

	Position cpos;
	Direction cdir = North;

	while (!path.eof())
	{
		char dir;
		int steps;

		path >> dir >> steps;
		path.ignore(1, ' ');

		rotate(cdir, dir == 'R');

		for (int i = 1; !has_visited_twice && i <= steps; ++i)
		{
			Position npos = advance_by(cpos, cdir, i);
			if (std::find(begin(stop_points), end(stop_points), npos) != end(stop_points))
			{
				has_visited_twice = true;
				visited_twice = npos;
			}
			else
			{
				stop_points.push_back(npos);
			}
		}

		cpos = advance_by(cpos, cdir, steps);
	}

	std::cout << std::abs(visited_twice.x) + std::abs(visited_twice.y) << std::endl;

	return EXIT_FAILURE;
}

#endif
