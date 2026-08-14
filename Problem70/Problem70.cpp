// Problem 70 Totient Permutation

#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

static void FillDigitsCount(std::vector<char>& digits, u32 nb)
{
	while (nb > 0)
	{
		char digit = nb % 10;
		digits[digit]++;
		nb /= 10;
	}
}

static bool IsPermutation(u32 lhs, u32 rhs)
{
	std::vector<char> digitCountsLhs(10, 0);
	std::vector<char> digitCountsRhs(10, 0);

	FillDigitsCount(digitCountsLhs, lhs);
	FillDigitsCount(digitCountsRhs, rhs);

	for (u32 i = 0; i < digitCountsLhs.size(); ++i)
	{
		if (digitCountsLhs[i] != digitCountsRhs[i])
			return false;
	}
	return true;
}

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

	float smallestRatio = std::numeric_limits<float>::max();
	u32 smallestRatioNb = 0;
	for (u32 i = 2; i < eulerTotients.size(); ++i)
	{
		if (!IsPermutation(i, eulerTotients[i]))
			continue;

		const float ratio = static_cast<float>(i) / eulerTotients[i];
		if (ratio < smallestRatio)
		{
			smallestRatio = ratio;
			smallestRatioNb = i;
			std::cout << i << ": " << ratio << std::endl;
		}
	}

	return smallestRatioNb;
}

int main()
{
	constexpr u32 upperBound = 10'000'000;
	const u32 sol = Solve(upperBound);
	std::cout << "Solution 70: " << sol << std::endl;

	return 0;
}