// Caution : this is horrideous.

#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <vector>
#include <string>

template<typename TT, typename OT>
TT sc(const OT val)
{
	return static_cast<TT>(val);
}

struct Sequence
{
	Sequence(std::string::iterator range_begin, std::string::iterator range_end, const size_t present_times) : range_begin(range_begin), range_end(range_end), present_times(present_times) {}

	std::string string() const
	{
		std::string full{range_begin, range_end};
		size_t last_marker_index = full.find_last_of(')');
		if (last_marker_index == std::string::npos)
			last_marker_index = 0;
		else
			last_marker_index += 1;
		return std::string{range_begin + last_marker_index, range_end};
	}

	size_t length() const
	{
		size_t last_marker_index = string().find_last_of(')');
		if (last_marker_index != std::string::npos)
			return sc<size_t>(std::distance(range_begin + static_cast<long>(last_marker_index), range_end));
		else
			return sc<size_t>(std::distance(range_begin, range_end));
	}

	std::vector<Sequence> subsequences;

	std::string::iterator range_begin, range_end;
	size_t present_times;
};

bool parse_subsequences(Sequence& sq)
{
	using namespace std;

	bool has_created_sequence = false;
	string::iterator marker_begin, marker_end, mul_it, current_it = sq.range_begin;
	while ((marker_end = find(current_it, sq.range_end, ')')) != sq.range_end) // find the next ')'
	{
		marker_begin = find(current_it, marker_end, '('); // find the matching '('...
		mul_it = find(marker_begin, marker_end, 'x'); // ... and 'x'

		if (mul_it != sq.range_end) // parse the genuine marker
		{
			size_t repeated_chars = stoul(string{marker_begin + 1, mul_it}),
				   repeated_times = stoul(string{mul_it + 1, marker_end});

			sq.subsequences.emplace_back(marker_end + 1, marker_end + 1 + static_cast<long>(repeated_chars), repeated_times);
			parse_subsequences(sq.subsequences.back());

			has_created_sequence = true;
			current_it = marker_end + sc<long>(repeated_chars);
		}
	}

	return has_created_sequence;
}

int main()
{
	using namespace std;

	ifstream in{"input.txt"};
	string raw{std::istreambuf_iterator<char>{in},
			   std::istreambuf_iterator<char>{}};

	raw.erase(remove(begin(raw), end(raw), '\n'), end(raw)); // Erase newlines (get rekt windows users)

	Sequence master{begin(raw), end(raw), 1};
	parse_subsequences(master);

	size_t parta_count = accumulate(begin(master.subsequences), end(master.subsequences), 0ul, [](size_t prev, Sequence& i) { return prev + i.length() * i.present_times; });

	std::string::iterator last_it = begin(raw);
	std::function<bool(size_t&, const size_t, Sequence&)> deep_sum = [&last_it, &deep_sum](size_t& count, const size_t node_present, Sequence& sq) {
		for (Sequence& subsq : sq.subsequences)
		{
			if (deep_sum(count, node_present * subsq.present_times, subsq))
			{
				count += subsq.length() * node_present;
				cout << "Linked subsequence found : " << subsq.string() << " repeated " << node_present << " times" << endl;

				if (std::distance(last_it, subsq.range_end) > 0)
					last_it = subsq.range_end;
			}
		}

		if (sq.subsequences.empty())
		{
			cout << "Reached unlinked subsequence : " << sq.string() << " repeated " << node_present << " times" << endl;
			count += sq.length() * node_present;

			if (std::distance(last_it, sq.range_end) > 0)
				last_it = sq.range_end;

			return false;
		}

		return true;
	};

	// Insert the last subsequences
	master.subsequences.emplace_back(begin(raw), std::find(begin(raw), end(raw), '('), 1);

	size_t partb_count = 0;
	deep_sum(partb_count, 1, master);

	master.subsequences.emplace_back(last_it, end(raw), 1);

	partb_count = 0;
	deep_sum(partb_count, 1, master); // ugly workaround to count the last uncompressed subsequence

	cout << "v1 size = " << parta_count << endl << "v2 size = " << partb_count;
}

