#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
	std::ifstream in{"input.txt"};

	size_t display_width = 50, display_height = 4;
	std::vector<bool> display;
	display.resize(display_width * display_height);

	for (std::string raw; std::getline(in, raw) && !raw.empty();)
	{
		std::stringstream rawss{raw};

		std::string command;
		rawss >> command;

		std::cout << raw << std::endl;

		if (command == "rect")
		{
			std::string size;
			rawss >> size;

			std::string::iterator cross_pos = std::find(begin(size), end(size), 'x');

			size_t width  = std::stoul(std::string{begin(size), cross_pos}),
				   height = std::stoul(std::string{cross_pos + 1, end(size)});

			for (size_t x = 0; x < width; ++x)
			for (size_t y = 0; y < height; ++y)
				display[x + (y * display_width)] = true;

		}
		else if (command == "rotate")
		{
			std::string mode;
			rawss >> mode;

			long index, by; // row/column index
			rawss.ignore(2, '='); // ignore ' x=' or ' y='
			rawss >> index;
			rawss.ignore(4); // ignore ' by '
			rawss >> by;

			if (mode == "row")
			{
				std::rotate(begin(display) + index, begin(display) + index + by, begin(display) + index + static_cast<long>(display_width));
			}
			else if (mode == "column")
			{
				// too lazy to make a vertical iterator
				for (size_t shift = 0; shift < static_cast<size_t>(by); ++shift)
				{
					for (size_t y = 0; y < display_height - 1; ++y)
						std::swap(display[static_cast<size_t>(index) + (y * display_width)], display[static_cast<size_t>(index) + ((y + 1) * display_width)]);
					std::swap(display[static_cast<size_t>(index)], display[static_cast<size_t>(index) + ((display_height - 1) * display_width)]);
				}
			}
		}

		//size_t pixel_count = 0;
		for (size_t y = 0; y < display_height; ++y)
		{
			for (size_t x = 0; x < display_width; ++x)
			{
				bool pixel = display[x + (y * display_height)];
				std::cout << (pixel ? '*' : '-');
				//pixel_count += pixel;
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;

		if (!rawss.eof())
			std::cout << "Warning : Some arguments were not handled." << std::endl;
	}

	//std::cout << pixel_count << std::endl;
}
