// Problem 92: Square Digit Chains

#include <cassert>
#include <format>
#include <iostream>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

static u64 SumOfDigitSquares(u64 nb)
{
	u64 newSum = 0;
	while (nb > 0)
	{
		const u64 digitSquare = (nb % 10) * (nb % 10);
		assert(newSum + digitSquare >= newSum);
		newSum += digitSquare;
		nb /= 10;
	}
	return newSum;
}

static u64 Solve(const u64 upperBound)
{
	// all nbs will end at 1, or 89
	u64 chainsThatEndAt89 = 0;

	for (u64 nb = 1; nb < upperBound; ++nb)
	{
		u64 curNb = nb;
		while (!(curNb == 1 || curNb == 89))
		{
			curNb = SumOfDigitSquares(curNb);
		}

		if (curNb == 89)
			++chainsThatEndAt89;
	}

	return chainsThatEndAt89;
}

int main()
{
	const u64 upperBound = 10'000'000;
	const u64 sol = Solve(upperBound);
	std::cout << "Solution 92: " << sol << std::endl;

	return 0;
}