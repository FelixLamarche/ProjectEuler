// Problem 76: Counting Summations

#include <cassert>
#include <iostream>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

static u32 SolveIter(int nb, int biggestTerm)
{
	if (nb < 0)
		return 0;
	if (nb <= 1)
		return 1;

	u32 sum = 0;
	// split up nb = i + {Sum of numbers n, where n <= i}
	for (int i = 1; i <= biggestTerm; ++i)
	{
		sum += SolveIter(nb - i, i);
	}
	return sum;
}

static u32 Solve(u32 upperBound)
{
	return SolveIter(upperBound, upperBound - 1);
}

int main()
{
	const u32 upperBound = 100;
	const u32 sol = Solve(upperBound);
	std::cout << "Solution 76: " << sol << std::endl;

	return 0;
}