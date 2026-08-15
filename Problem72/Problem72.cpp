// Problem 72: Counting Fractions

#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

static u64 Solve(u32 upperBound)
{
	// Count the number of proper fractions between [0, upperBound]

	// Should just be adding up the euler totient of every number, as we get the count of numbers which are co-prime

	std::vector<u64> eulerTotients(upperBound + 1);

	std::iota(eulerTotients.begin(), eulerTotients.end(), 0);
	eulerTotients[1] = 0;

	for (u32 nb = 2; nb < eulerTotients.size(); ++nb)
	{
		// euler totient is always n - 1 for a number n, if it is prime
		const bool isPrime = eulerTotients[nb] == nb;
		if (!isPrime)
			continue;

		eulerTotients[nb]--;

		for (u32 multiple = 2 * nb; multiple < eulerTotients.size(); multiple += nb)
		{
			u64& eulerTotient = eulerTotients[multiple];
			eulerTotient *= nb - 1;
			eulerTotient /= nb; // as it is a multiple, it can always be evenly divided by its prime factor
		}
	}

	u64 s = 0;
	return std::accumulate(eulerTotients.begin(), eulerTotients.end(), s);
}

int main()
{
	constexpr u32 upperBound = 1'000'000;
	const u64 sol = Solve(upperBound);
	std::cout << "Solution 72: " << sol << std::endl;

	return 0;
}