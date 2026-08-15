// Problem 77: Prime Summations

#include <cassert>
#include <iostream>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

static bool IsPrime(int nb)
{
	for (int divider = 2; divider < nb; ++divider)
	{
		if (nb % divider == 0)
			return false;
	}
	return true;
}

static u32 SolveIter(const std::vector<int>& primes, int nb, int maxPrimeIdx)
{
	if (nb < 0)
		return 0;
	if (nb == 0)
		return 1;

	u32 sum = 0;
	for (int primeIdx = 0; primeIdx <= maxPrimeIdx; ++primeIdx)
	{
		const int prime = primes[primeIdx];
		sum += SolveIter(primes, nb - prime, primeIdx);
	}
	return sum;
}

static u32 Solve(u32 summationCount)
{
	u32 bestCount = 0;
	int bestNb = 0;

	int nb = 2;
	std::vector<int> primesUpToNb;

	while (bestCount < summationCount)
	{
		const u32 count = SolveIter(primesUpToNb, nb, primesUpToNb.size() - 1);

		if (IsPrime(nb))
			primesUpToNb.push_back(nb);

		std::cout << nb << ": " << count << std::endl;

		if (count > bestCount)
		{
			bestCount = count;
			bestNb = nb;
		}

		++nb;
	}

	return bestNb;
}

int main()
{
	const u32 primeSummationCountBound = 5000;
	const u32 sol = Solve(primeSummationCountBound);
	std::cout << "Solution 77: " << sol << std::endl;

	return 0;
}