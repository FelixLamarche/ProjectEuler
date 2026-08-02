// Problem 65: Convergents of e

#include "../Utils/UnsignedBigInt.h"

#include <assert.h>
#include <format>
#include <iostream>
#include <numeric>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(0)
#define LOGFMT(str, ...) do { std::cout << std::format(str, __VA_ARGS__); } while(0)

static u32 Solve(const u32 stepCount)
{
	// Continued fraction of e is such: [2;1,2,1,1,4,1,1,6,1,1,8,1,1,2k,1,1,2(k+1),...]

	std::vector<u32> sequence;
	sequence.reserve(stepCount);
	sequence.push_back(2);
	sequence.push_back(1);
	sequence.push_back(2);

	for (int i = 3; i < stepCount; ++i)
	{
		if ((i - 2) % 3 == 0)
			sequence.push_back(2 + 2 * (i - 2) / 3);
		else
			sequence.push_back(1);
	}

	int seqIdx = sequence.size() - 1;
	uBigInt num = sequence[seqIdx];
	uBigInt denom = 1;
	seqIdx--;
	for (; seqIdx >= 0; --seqIdx)
	{
		const uBigInt temp = num;
		num = denom;
		denom = temp;

		num += sequence[seqIdx] * denom;
	}

	LOGFMT("{}/{}\n", num.ToString(), denom.ToString());

	u32 digitsSum = 0;
	while (num > 0)
	{
		digitsSum += static_cast<u32>(num % 10);
		num /= 10;
	}

	return digitsSum;
}

void main()
{
	constexpr u32 maxConvergents = 100;
	const u32 sol = Solve(maxConvergents);
	std::cout << "Solution 65: " << sol << std::endl;
}