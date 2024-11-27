#include "Problem6.h"

#include <numeric>

long long Problem6::Solve(int n)
{
	long long sumSquares = 0;
	for (long long i = 1; i <= n; i++)
	{
		sumSquares += i * i;
	}

	long long squareOfSum = (n * (n + 1)) / 2;
	squareOfSum *= squareOfSum;

	return std::abs(sumSquares - squareOfSum);
}