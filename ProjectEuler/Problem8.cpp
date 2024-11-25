#include "Problem8.h"

#include <numeric>
#include <string>
#include <vector>

int Problem8::Solve(const std::string& nbStr, int consecutive)
{
	std::vector<char> digits;
	digits.reserve(nbStr.size());
	for (size_t i = 0; i < nbStr.size(); i++)
	{
		// Go from ascii to nbs
		digits.push_back(nbStr[i] - '0');
	}

	int biggest = 0;
	for (size_t start = 0; start + consecutive <= nbStr.size(); start++)
	{
		int cur = 1;
		for (int i = 0; i < consecutive; i++)
		{
			cur *= digits[start + i];
		}
		biggest = std::max(biggest, cur);
	}
	return biggest;
}
