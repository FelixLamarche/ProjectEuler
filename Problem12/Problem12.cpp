#include "Problem12.h"

#include <map>
#include <numeric>

int Problem12::GetNbDivider(long long N)
{
	const long long square = static_cast<long long>(sqrtl(static_cast<long double>(N)));

	int dividers = 2; // 1 And N
	for (long long i = 2; i <= square; i++)
	{
		if (N % i == 0)
		{
			dividers += 2; // i and its counterpart, as they are not square
		}
	}
	if (square * square == N)
	{
		dividers--; // We count squares twice, so remove one
	}
	return dividers;
}


/// Triangle number: sum of the natural numbers 1=1, 1+2=3, 1+2+3=6, etc.
/// Find the smallest triangle number with N divisors
long long Problem12::Solve(int N)
{
	static std::map<long long, std::pair<long long, long long>> divisorCountToNbAndSum{ {1, {1, 1}} };

	long long dividerCount = 1;
	long long sum = 1;
	long long nb = 1;
	auto it = divisorCountToNbAndSum.upper_bound(N);
	if (it == divisorCountToNbAndSum.end())
	{
		--it;
	}

	dividerCount = it->first;
	nb = it->second.first;
	sum = it->second.second;

	while (dividerCount <= N)
	{
		sum += ++nb;
		dividerCount = GetNbDivider(sum);

		// We count in ascending order, the first dividerCount found
		// is always the lowest number
		long long prevDivider = dividerCount;
		while (!divisorCountToNbAndSum.contains(prevDivider))
		{
			divisorCountToNbAndSum[prevDivider] = { nb, sum };
			--prevDivider;
		}
	}

	return sum;
}