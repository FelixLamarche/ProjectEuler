// Problem 66: Diophantine Equations

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

static u32 Solve(const u32 maxD)
{
	u64 maxX_D = 0;
	u64 maxX = 0;

	u64 maxOverflowX = std::sqrt(std::numeric_limits<unsigned long long>::max());

	for (u64 D = 1; D <= maxD; ++D)
	{
		// No solutions when D is a square number
		const double sqrtD = sqrt(D);
		if (sqrtD == ceil(sqrtD))
			continue;

		u64 x = 1;
		while (true)
		{
			// Equation to try and get:
			// x^2 - D*y^2 = 1
			assert(x > maxOverflowX, "Overflow");

			const u64 y2 = (x * x - 1) / D;

			if (y2 <= 0)
			{
				++x;
				continue;
			}

			if (y2 * D != (x * x - 1))
			{
				++x;
				continue;
			}

			const u64 y = sqrt(y2);
			if (y * y != y2)
			{
				++x;
				continue;
			}

			break;
		}

		LOGFMT("D:{}\n", D);
		if (x > maxX)
		{
			LOGFMT("Max X='{}', D='{}'\n", x, D);
			maxX = x;
			maxX_D = D;
		}
	}

	return maxX_D;
}

void main()
{
	constexpr u32 maxD = 1000;
	const u32 sol = Solve(maxD);
	std::cout << "Solution 66: " << sol << std::endl;
}