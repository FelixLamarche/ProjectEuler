// Problem 48 Self Powers
// The series, 1^1 + 2^2 + 3^3 + 4^4 + ... + 10^10 = 10405071317
// Find the last ten digits of the series Sum of n^n from 1 to 1000
// 1^1 + 2^2 + 3^3 + ... + 1000^1000

#include <iostream>

using int64 = long long;

static int64 Solve()
{
	// Only numbers modulo the digits which matter can actually influence the ending digits about which we care about
	constexpr int64 maximalAmount = 10'000'000'000; // 10 digits means 10^10

	int64 solution = 0;

	constexpr int64 maxN = 1000;
	for (int64 n = 1; n <= maxN; ++n)
	{
		int64 selfPower = 1;
		for (int64 power = 1; power <= n; ++power)
		{
			selfPower = (selfPower * n) % maximalAmount;
		}

		solution = (solution + selfPower) % maximalAmount;
	}

	return solution;
}

void main()
{
	const int64 solution = Solve();
	std::cout << "Problem 48 Solution: " << solution << std::endl;
}