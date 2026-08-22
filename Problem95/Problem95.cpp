// Problem 95 : Amicable Chains

#include <cassert>
#include <format>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

static u32 SumOfProperDivisors(const u32 nb)
{
	if (nb <= 1)
		return 0;

	u32 sum = 1; // 1 is always a proper divisor
	const u32 upperNb = sqrt(nb);
	for (u32 divider = 2; divider <= upperNb; ++divider)
	{
		if (nb % divider == 0)
		{
			if (divider * divider == nb)
				sum += divider;
			else
				sum += divider + nb / divider;
		}
	}
	return sum;
}

static u32 Solve(u32 upperBound)
{
	u32 smallestMemberOfLongestChain = 0;
	u32 longestChainLength = 0;

	constexpr u32 uninitializedSum = std::numeric_limits<u32>::max();
	std::vector<u32> numbersSumOfProperDivisors(upperBound + 1, uninitializedSum);
	std::vector<u32> chainNbs;
	for (u32 nb = 2; nb <= upperBound; ++nb)
	{
		chainNbs.clear();

		u32 curNb = nb;
		bool isChainOutsideBounds = false;
		while (std::find(chainNbs.begin(), chainNbs.end(), curNb) == chainNbs.end() && !isChainOutsideBounds)
		{
			chainNbs.push_back(curNb);
			u32 properDivisorsSum = numbersSumOfProperDivisors[curNb];
			if (properDivisorsSum == uninitializedSum)
			{
				properDivisorsSum = SumOfProperDivisors(curNb);
				numbersSumOfProperDivisors[curNb] = properDivisorsSum;
			}
			curNb = properDivisorsSum;
			isChainOutsideBounds = isChainOutsideBounds || curNb > upperBound || curNb <= 1;
		}

		if (!isChainOutsideBounds)
		{
			auto chainStartIt = std::find(chainNbs.begin(), chainNbs.end(), curNb);
			const u32 chainLength = (chainNbs.end() - chainStartIt) / sizeof(u32);
			if (chainLength > longestChainLength)
			{
				longestChainLength = chainLength;
				smallestMemberOfLongestChain = *std::min_element(chainStartIt, chainNbs.end());
			}
		}
	}

	return smallestMemberOfLongestChain;
}

int main()
{
	const u32 upperBound = 1000000;
	const u32 sol = Solve(upperBound);
	std::cout << "Solution 95: " << sol << std::endl;

	return 0;
}