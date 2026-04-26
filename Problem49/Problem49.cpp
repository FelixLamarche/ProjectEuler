// Problem 49 Prime Permutations

#include <iostream>
#include <vector>

using int64 = long long;
using uint = unsigned int;

static uint GetDigitsFlag(int nb)
{
	uint digitsFlag = 0;

	while (nb > 0)
	{
		int digit = nb % 10;
		uint digitFlag = 1 << digit;
		digitsFlag |= digitFlag;

		nb /= 10;
	}

	return digitsFlag;
}

static int64 Solve()
{
	std::vector<bool> primeSieve(10'000, true);
	primeSieve[0] = false;
	primeSieve[1] = false;

	for (int n = 2; n < primeSieve.size(); ++n)
	{
		for (int multiple = 2 * n; multiple < primeSieve.size(); multiple += n)
		{
			primeSieve[multiple] = false;
		}
	}

	constexpr int knownSolution = 1487;
	constexpr int gap = 3330;
	constexpr int consecutiveCount = 3;

	int nb;
	for (nb = 1000; nb < 10'000 - ((consecutiveCount - 1) * gap); ++nb)
	{
		if (nb == knownSolution)
			continue;

		const uint nbDigitsFlag = GetDigitsFlag(nb);
		int count = 0;
		int sequenceNb = nb;
		while (count < consecutiveCount)
		{
			if (!primeSieve[sequenceNb])
				break;

			if (GetDigitsFlag(sequenceNb) != nbDigitsFlag)
				break;

			sequenceNb += gap;
			++count;
		}	

		if (count == consecutiveCount)
			break;
	}

	int64 solution = 0;
	for (int nbIdx = 0; nbIdx < consecutiveCount; ++nbIdx)
	{
		int64 sequenceNb = nb + nbIdx * gap;
		solution *= 10000;
		solution += sequenceNb;
	}
	return solution;
}

void main()
{
	const int64 solution = Solve();
	std::cout << "Problem 49 Solution: " << solution << std::endl;
}
