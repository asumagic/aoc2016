/*#include <algorithm>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <array>

size_t count_index(const char in)
{
	return static_cast<size_t>(in) - 'a';
}

constexpr size_t alphabet_size = 'z' - 'a' + 1;

void decypher(char& c, const size_t rotation)
{
	if (isalpha(c))
		c += rotation - (static_cast<size_t>(c) + rotation <= 'z' ? 0 : alphabet_size);
}

int main()
{
	std::ifstream in{"input.txt"};

	for (std::string raw; std::getline(in, raw);)
	{
		const auto it_sid = std::find_if(begin(raw), end(raw), isdigit);
		const auto it_chk = std::find(begin(raw), end(raw), '[');

		std::string encrypted{begin(raw), it_sid - 1}, chk{it_chk + 1, end(raw) - 1};
		size_t sid = std::stoul(std::string{it_sid, it_chk});

		std::array<size_t, alphabet_size> count_of{};
		std::for_each(begin(encrypted), end(encrypted), [&count_of](const char c) { if (isalpha(c)) ++count_of[count_index(c)]; });

		bool real = true;
		size_t last_count = count_of[count_index(chk[4])]; // 5th checksum occurrences
		for (size_t i = 0; i < 4; ++i)
		{
			size_t cchar = count_index(chk[i]), nchar = count_index(chk[i + 1]),
				   ccount = count_of[cchar], ncount = count_of[nchar];

			if ((ccount < ncount) || // If the next char is more present than the current char
			   ((ccount == ncount) && (cchar > nchar))) // Break ties with the order
			{
				real = false; // Invalid checksum, skipping
				break;
			}

			count_of[cchar] = 0;
		}

		if (real && std::find_if(begin(count_of), end(count_of), [last_count](const size_t ccount) { return last_count > ccount; }) != end(count_of))
		{
			std::string decoded = encrypted;
			const size_t rotate_by = static_cast<size_t>(sid) % alphabet_size;
			std::for_each(begin(decoded), end(decoded), [rotate_by](char& i) { decypher(i, rotate_by); });

			if (decoded == "northpole-object-storage")
				std::cout << decoded << " = " << sid << std::endl;
		}
	}
}
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#define w string
#define b begin
#define u b(r),end(r)
using namespace std;int main(){fstream f{"input.txt"};for(w r;getline(f,r);){auto i=find_if(u,::isdigit),j=find(u,'[');w n{b(r),b(r)+3};int s=stoi(w{i,j});for(char&c:n)c+=s%26-(c+s%26<'{'?0:26);if(n=="nor")cout<<s;}}
