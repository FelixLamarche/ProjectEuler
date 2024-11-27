#include "Problem9.h"

#include <numeric>
#include <unordered_map>

int Problem9::Solve(int N)
{
	static std::unordered_map<int, int> cache;

	// To generate pythagorean triplets, there is Euclids formula:
	// for m > n > 0
	// a = k * (m^2 - n^2)
	// b = k * (2mn)
	// c = k * (m^2 + n^2)

	// For a + b + c = N
	// 2km^2 + 2kmn = N
	// 2km(m + n) = N
	// (N / 2km) - m = n

	if (cache.count(N) > 0)
	{
		return cache[N];
	}

	int biggest = -1;
	for (int n = 1; n <= N / 3; n++)
	{
		for (int m = n + 1; m <= N / 2; m++)
		{
			for (int k = 1; 2 * k * m * m + 2 * k * m * n <= N; k++)
			{
				int a = k * (m * m - n * n);
				int b = k * 2 * m * n;
				int c = k * (m * m + n * n);

				if (a + b + c == N)
				{
					biggest = std::max(biggest, a * b * c);
				}
			}
		}
	}

	cache[N] = biggest;

	return biggest;
}