#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	std::ifstream in{"input.txt"};

	std::vector<int> v;
	while (!in.eof())
	{
		int to_append;
		in >> to_append;
		v.push_back(to_append);
	}

	const size_t s1 = 1 * 3, s2 = 2 * 3;

	int valid_count = 0;
	for (size_t j = 0; j < 3; ++j)
	for (size_t i = j; i < v.size(); i += 3 * 3)
		valid_count += (v[i] + v[i + s1] > v[i + s2]) && (v[i] + v[i + s2] > v[i + s1]) && (v[i + s1] + v[i + s2] > v[i]);

	std::cout << valid_count;
}
