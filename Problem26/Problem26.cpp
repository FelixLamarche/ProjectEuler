/// Problem 26: Reciprocal cycles
/// Find the value of d < N for which 1/d contains the longest recurring cycle in its decimal fraction part.
/// N <= 10000
#include <iostream>
#include <map>
#include <vector>

static int Solve(int N)
{
	static std::vector<int> cycleLengths = { 0, 0 };

	cycleLengths.reserve(N);
	for (int d = static_cast<int>(cycleLengths.size()); d < N; ++d)
	{
		// Do long division,
		// Stop if the remainder is 0 - meaning the decimal is finite
		// Or if the remainder repeats - meaning the decimal is infinite, and we have reached the cycle
		std::map<int, int> remainders;
		int remainder = 1; // Start as 1/d with 1 as the remainder
		int cycle = 0;

		while (!remainders.count(remainder) && remainder != 0)
		{
			remainders.insert({ remainder, cycle });
			++cycle;
			remainder = (remainder * 10) % d;
		}

		if (remainder == 0)
		{
			cycleLengths.push_back(0);
		}
		else
		{
			const int startOfCycle = remainders[remainder];
			cycleLengths.push_back(cycle - startOfCycle);
		}
	}

	int maxCycle = 0;
	int maxD = 0;
	for (int i = 2; i < N; ++i)
	{
		if (cycleLengths[i] > maxCycle)
		{
			maxCycle = cycleLengths[i];
			maxD = i;
		}
	}
	return maxD;
}

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; ++i)
	{
		int N;
		std::cin >> N;
		std::cout << Solve(N) << std::endl;
	}
	return 0;
}