/// Problem 22: Names scores
/// Given N names, sort them into alphabetical order, and find their name scores.
/// The name score being the sum of the alphabetical value of each letter in the name, multiplied by its position in the list.
/// Then given Q queries, return the values of the Q names.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static constexpr int NameScore(const std::string& name)
{
	int score = 0;
	for (const char c : name)
	{
		score += c - 'A' + 1;
	}
	return score;
}

int main()
{
	int N;
	std::cin >> N;
	std::vector<std::string> names(N);
	for (int i = 0; i < N; i++)
	{
		std::cin >> names[i];
	}
	std::sort(names.begin(), names.end());

	int Q;
	std::cin >> Q;
	std::vector<std::string> queries(Q);
	for (int i = 0; i < Q; i++)
	{
		std::cin >> queries[i];
		const auto it = std::equal_range(names.begin(), names.end(), queries[i]);

		if (it.first != it.second)
		{
			const int position = static_cast<int>(it.first - names.begin() + 1);
			const int score = NameScore(queries[i]) * position;
			std::cout << score << std::endl;
		}
		else
		{
			std::cout << "0" << std::endl;
		}
	}

	return 0;
}