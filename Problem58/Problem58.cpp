// Problem 58: Spiral Primes
#include <format>
#include <iostream>
#include <vector>

using u64 = unsigned long long;
using u32 = unsigned long;

static bool IsPrime(u64 nb)
{
	u64 rootLimit = ceil(sqrt(nb));
	if (rootLimit == nb)
		rootLimit--;

	for (u64 divider = 2; divider <= rootLimit; divider++)
	{
		if (nb % divider == 0)
			return false;
	}
	return true;
}

static u64 Solve(float minRatio)
{
	float ratio = 1.f;

	u64 diagonalNbsCount = 1;
	u64 primeDiagonalNbsCount = 0;

	u64 nb = 1;
	u64 sideLength = 0;
	while (ratio >= minRatio)
	{
		sideLength += 2;
		for (u32 side = 0; side < 4; side++)
		{
			nb += sideLength;
			if (IsPrime(nb))
				primeDiagonalNbsCount++;
			diagonalNbsCount++;
		}

		ratio = static_cast<float>(primeDiagonalNbsCount) / diagonalNbsCount;
	}

	u64 squareSideLength = sideLength + 1;
	return squareSideLength;
}

void main()
{
	constexpr float minRatio = 0.1f;
	u64 sol = Solve(minRatio);
	std::cout << "Solution 58: " << sol << std::endl;
}
