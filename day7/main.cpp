#include <algorithm>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>

template<typename RAI_t>
bool has_abba_sequence(const RAI_t _begin, const RAI_t _end) // Returns whether an ABBA sequence is present in the iterator range.
{
	if (std::distance(_begin, _end) < 4)
		return false;

	for (RAI_t c = _begin; c != _end - 3; ++c)
		if ((c[0] == c[3]) && (c[1] == c[2]) && (c[0] != c[1]))
				return true;

	return false;
}

bool supports_tls(std::string raw)
{
	std::string::iterator current_it = begin(raw), bracket_it, endbracket_it;
	std::vector<std::pair<std::string::iterator, std::string::iterator>> sequences;
	while ((bracket_it = std::find(current_it, end(raw), '[')) != end(raw)) // Handle hypernet sequences
	{
		endbracket_it = std::find(bracket_it, end(raw), ']');
		if (has_abba_sequence(bracket_it, endbracket_it))
			return false; // If an IPv7 address hypernet sequence contains an ABBA sequence, it doesn't support TLS.

		sequences.emplace_back(current_it, bracket_it);
		current_it = endbracket_it + 1;
	}
	sequences.emplace_back(current_it, end(raw));

	for (auto seq : sequences)
		if (has_abba_sequence(seq.first, seq.second))
			return true;

	return false;
}

int main()
{
	std::ifstream in{"input.txt"};

	size_t match_count = 0;
	for (std::string raw; std::getline(in, raw);)
		if (supports_tls(raw))
			++match_count;

	std::cout << match_count << std::endl;
}
