// Problem 69: Totient Maximum

#include <iostream>
#include <numeric>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

static u32 Solve(u32 upperBound)
{
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

	float biggestRatio = 0.f;
	u32 biggestRatioNb = 0;
	for (u32 i = 2; i < eulerTotients.size(); ++i)
	{
		const float ratio = static_cast<float>(i) / eulerTotients[i];
		if (ratio > biggestRatio)
		{
			biggestRatio = ratio;
			biggestRatioNb = i;
			std::cout << i << ": " << ratio << std::endl;
		}
	}

	return biggestRatioNb;
}

int main()
{
	constexpr u32 upperBound = 1'000'000;
	const u32 sol = Solve(upperBound);
	std::cout << "Solution 69: " << sol << std::endl;

	return 0;
}