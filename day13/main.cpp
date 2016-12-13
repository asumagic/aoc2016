#include <algorithm>
#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>

struct Pos
{
	size_t x, y;
	bool operator==(const Pos other) const { return x == other.x && y == other.y; }
};

constexpr size_t grid_size = 100;

int main()
{
	size_t seed = 1364;
	std::vector<std::vector<char>> map(grid_size, std::vector<char>(grid_size));

	for (size_t y = 0; y < map.size() - 2; ++y) // keep an offset on the edges
	for (size_t x = 0; x < map.size() - 2; ++x)
	{
		std::bitset<16> bs{(x*x + 3*x + 2*x*y + y + y*y) + seed};
		map[x+1][y+1] = (bs.count() % 2 ? '#' : '.');
	}
	map[2][2] = 'O';

	std::vector<std::vector<char>> mapf = map;

	size_t ccount = 0;
	for (int i = 0; i < 51; ++i)
	{
		ccount = 0;
		for (size_t x = 1; x < map.size() - 1; ++x)
		for (size_t y = 1; y < map.size() - 1; ++y)
		{
			if (map[x][y] == 'O')
			{
				if (mapf[x-1][y] != '#') mapf[x-1][y] = 'O'; // sorry
				if (mapf[x][y-1] != '#') mapf[x][y-1] = 'O';
				if (mapf[x+1][y] != '#') mapf[x+1][y] = 'O';
				if (mapf[x][y+1] != '#') mapf[x][y+1] = 'O';
				++ccount;
			}
		}

		map = mapf;
	}

	std::cout << ccount << std::endl;
}
