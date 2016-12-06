#include <algorithm>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <string>
#include "md5.hpp"

using namespace std::chrono;

time_point<system_clock> pt;

void h4x(const std::string code)
{
	std::cout << " \033[1;32m" << std::vector<std::string>{"[  HACKING  ]",
														   "[   HACKING ]",
														   "[    HACKING]",
														   "[G    HACKIN]",
														   "[NG    HACKI]",
														   "[ING    HACK]",
														   "[KING    HAC]",
														   "[CKING    HA]",
														   "[ACKING    H]",
														   "[HACKING    ]",
														   "[ HACKING   ]",
														   "[  HACKING  ]",
														   "[           ]",
														   "[  HACKING  ]",
														   "[           ]",}[(duration_cast<milliseconds>(system_clock::now() - pt).count() / 200) % 15] << " " <<
				 std::setfill(' ') << std::setw(3) << static_cast<int>((static_cast<float>((8 - std::count(begin(code), end(code), '_'))) / 8.f) * 100.f) << "% ";
	for (const char c : code)
	{
		if (c == '_')
		{
			if (rand() % 20 == 0)
				std::cout << "\033[1;41m";

			std::cout << "\033[1;32m" << static_cast<char>((rand() % ('~' - '!')) + '!') << "\033[0m";
		}
		else
		{
			std::cout << "\033[1;92m" << c;
		}
	}
	std::cout << "\033[0m\r" << std::flush;
}

int main()
{
	std::string steak, code{"________"};
	std::cin >> steak;

	pt = system_clock::now();

	for(size_t i = 0, left = 8;; ++i)
	{
		std::string hashed = md5(steak + std::to_string(i)); // STEAK HASHÉ!!11!1!11
		if (std::distance(begin(hashed), std::find_if(begin(hashed), end(hashed), [](const char i) { return i != '0'; })) >= 5)
		{
			size_t at = static_cast<size_t>(hashed[5]) - '0';
			if (code[at] == '_' && at < 8)
			{
				code[at] = hashed[6];
				h4x(code);

				if (--left == 0)
					break;
			}
		}

		if (i % 500 == 0)
			h4x(code);
	}

	std::cout << std::endl;
}
