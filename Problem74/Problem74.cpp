// Problem 74: Digit Factorial Chains

#include <cassert>
#include <iostream>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

static u64 DigitFactorial(u64 nb)
{
	switch (nb)
	{
	case 0:
		return 1;
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 6;
	case 4:
		return 24;
	case 5:
		return 120;
	case 6:
		return 720;
	case 7:
		return 5040;
	case 8:
		return 40320;
	case 9:
		return 362880;
	}
	return 0;
}

static u64 FactorialSumOfDigits(u64 nb)
{
	u64 newSum = 0;
	while (nb > 0)
	{
		const u64 digitFactorial = DigitFactorial(nb % 10);
		assert(newSum + digitFactorial >= newSum);
		newSum += digitFactorial;
		nb /= 10;
	}
	return newSum;
}

static u32 Solve(u32 upperBound, u32 chainLength)
{
	u32 chainsOfLength = 0;

	for (u64 nb = 1; nb < upperBound; ++nb)
	{
		std::vector<u64> chainNbs;
		u64 curChainNb = nb;
		while (std::find(chainNbs.begin(), chainNbs.end(), curChainNb) == chainNbs.end())
		{
			chainNbs.push_back(curChainNb);
			curChainNb = FactorialSumOfDigits(curChainNb);
		}

		if (chainNbs.size() == chainLength)
			++chainsOfLength;
	}

	return chainsOfLength;
}

int main()
{
	const u32 upperBound = 1'000'000;
	const u32 chainLength = 60;
	const u32 sol = Solve(upperBound, chainLength);
	std::cout << "Solution 74: " << sol << std::endl;

	return 0;
}