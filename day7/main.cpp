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

template<typename T>
void vector_append(std::vector<T>& target, std::vector<T> to_append)
{
	target.insert(end(target), begin(to_append), end(to_append));
}

template<typename RAI_t>
std::vector<std::string> get_aba_bab_sequences(const RAI_t _begin, const RAI_t _end) // Returns all the ABA and BAB candidates in the iterator range; only including the two first letters in the right order
{
	std::vector<std::string> sequences;
	if (std::distance(_begin, _end) >= 3)
		for (RAI_t c = _begin; c != _end - 1; ++c)
			if (c[0] == c[2])
				sequences.emplace_back(c, c + 2);

	return sequences;
}

bool supports_ssl(std::string raw)
{
	std::string::iterator current_it = begin(raw), bracket_it, endbracket_it;
	std::vector<std::string> aba_sequences, bab_sequences;
	while ((bracket_it = std::find(current_it, end(raw), '[')) != end(raw)) // Handle hypernet sequences
	{
		endbracket_it = std::find(bracket_it, end(raw), ']');
		vector_append(bab_sequences, get_aba_bab_sequences(bracket_it, endbracket_it));
		vector_append(aba_sequences, get_aba_bab_sequences(current_it, bracket_it));
		current_it = endbracket_it + 1;
	}
	vector_append(aba_sequences, get_aba_bab_sequences(current_it, end(raw)));

	for (std::string aba_seq : aba_sequences)
		for (std::string bab_seq : bab_sequences)
			if (aba_seq[0] == bab_seq[1] && aba_seq[1] == bab_seq[0])
				return true;

	return false;
}

int main()
{
	std::ifstream in{"input.txt"};

	size_t tls_count = 0, ssl_count = 0;
	for (std::string raw; std::getline(in, raw);)
	{
		if (supports_tls(raw))
			++tls_count;
		if (supports_ssl(raw))
			++ssl_count;
	}

	std::cout << tls_count << " addresses supports TLS." << std::endl << ssl_count << " addresses supports SSL." << std::endl;
}
