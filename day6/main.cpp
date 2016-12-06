#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
	std::ifstream in{"input.txt"};

	std::vector<std::string> lines;
	for (std::string line; std::getline(in, line);)
		if (!line.empty())
			lines.push_back(line);

	std::string decoded;
	for (size_t col = 0; col < lines[0].size(); ++col)
	{
		std::array<size_t, 128> count_of{};
		for (size_t row = 0; row < lines.size(); ++row)
			++count_of[static_cast<size_t>(lines[row][col])];

		size_t smallest = static_cast<size_t>(-1); char smallest_index = 0; // sorry
		for (size_t i = 0; i < count_of.size(); ++i) // deeply sorry
		{
			if (count_of[i] != 0 && count_of[i] < smallest)
			{
				smallest = count_of[i];
				smallest_index = static_cast<char>(i);
			}
		}

		decoded.push_back(smallest_index);
	}

	std::cout << decoded << std::endl;
}
