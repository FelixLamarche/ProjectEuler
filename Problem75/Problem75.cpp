// Problem 75: Singular Integer Right Triangles

#include <cassert>
#include <iostream>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

static bool AreCoprime(u64 a, u64 b)
{
	const u64 max = std::max(a, b);
	const u64 min = std::min(a, b);
	for (u64 divider = 2; divider <= min; ++divider)
	{
		if (min % divider == 0 && max % divider == 0)
			return false;
	}
	return true;
}

static u32 Solve(u32 upperBound)
{
	std::vector<u32> rightTriangleCounts(upperBound + 1, 0);

	//for (u64 b = 2; b < upperBound / 2; ++b)
	//{
	//	const u64 b2 = b * b;
	//	for (u64 a = 1; a < b; ++a)
	//	{
	//		const u64 c = std::sqrt(b2 + a * a);
	//		if (a + b + c > upperBound)
	//			break;

	//		if (c * c == b2 + a * a)
	//			rightTriangleCounts[a + b + c]++;
	//	}
	//}

	//Euclid's formula to generate pythagorean triplet:
	// a = m^2 - n^2, b = 2mn c = m^2 + n^2
	// where m > n > 0

	for (u64 m = 2; m < upperBound; ++m)
	{
		bool hasReachedBound = false;

		for (u64 n = 1; n < m; ++n)
		{
			// This formula works to generate primitives only if m or n is odd
			if (m % 2 == 1 && n % 2 == 1)
				continue;
			if (m % 2 == 0 && n % 2 == 0)
				continue;

			// m and n have to be coprime
			if (!AreCoprime(m, n))
				continue;

			const u64 a = m * m - n * n;
			const u64 b = 2 * m * n;
			const u64 c = m * m + n * n;
			const u64 perimeter = a + b + c;

			if (perimeter > upperBound)
			{
				break;
			}

			u64 k = 1;
			while (k * perimeter <= upperBound)
			{
				++rightTriangleCounts[k * perimeter];
				k++;
			}
		}
	}

	return std::count(rightTriangleCounts.begin(), rightTriangleCounts.end(), 1);
}

int main()
{
	const u32 upperBound = 1'500'000;
	const u32 sol = Solve(upperBound);
	std::cout << "Solution 75: " << sol << std::endl;

	return 0;
}