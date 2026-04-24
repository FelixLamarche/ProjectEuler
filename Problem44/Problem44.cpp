// Problem 44 Pentagon Numbers
// A pentagonal number Pn= n*(3n - 1)/2 which follows the sequence: 1,5,12,22,35,...
// Find the first pair of pentagonal numbers Pj and Pk for which their sum and difference are pentagonal and D = |Pk - Pj| is minimised; What is the value of D?

#include <iostream>
#include <limits>

using int64 = long long;

#define LOGF(str, ...) do { printf(str, __VA_ARGS__);} while(0)

static int64 PentagonalNumber(int64 n)
{
	return n * (3 * n - 1) / 2;
}

// Inefficient but valid
static bool IsPentagonalNumber(int64 nb)
{
	int64 pentagonalNumber = 0;
	for (int64 n = 1; pentagonalNumber < nb; ++n)
		pentagonalNumber = PentagonalNumber(n);

	return pentagonalNumber == nb;
}

static int64 Solve()
{
	constexpr int64 upperBound = 2'500;

	int64 difference = LLONG_MAX;

	for (int64 n1 = 1; n1 < upperBound; ++n1)
	{
		const int64 pentagonal1 = PentagonalNumber(n1);
		for (int64 n2 = 1; n2 < n1; ++n2)
		{
			const int64 pentagonal2 = PentagonalNumber(n2);

			const int64 diff = pentagonal1 - pentagonal2;
			const int64 sum = pentagonal1 + pentagonal2;

			if (IsPentagonalNumber(diff) && IsPentagonalNumber(sum))
			{
				LOGF("n1, n2, penta1, penta2, diff, sum, %lli, %lli, %lli, %lli, %lli, %lli\n", n1, n2, pentagonal1, pentagonal2, diff, sum);
				difference = std::min(difference, diff);
			}
		}
	}
	return difference;
}

void main()
{
	const int64 solution = Solve();
	std::cout << "Problem 44 Solution :" << solution << std::endl;
}