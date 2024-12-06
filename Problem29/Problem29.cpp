// Problem 29: Distinct powers
// How many distinct terms are in the sequence a^b for 2 <= a <= N and 2 <= b <= N?
// While NOT counting repeats.

#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

static long long Solve(int N)
{
	const int nbPrimes = N * static_cast<int>(std::ceil(std::log2(N)));
	//const std::vector<bool> primeSieve = CreateSieve(nbPrimes);
	std::vector<bool> isPower(N + 1, false);

	long long count = 0;
	for (long long a = 2; a <= N; a++)
	{
		// If the number is a power of a previous number, it was already counted
		if (isPower[a])
		{
			continue;
		}

		// Count the powers of a within N
		// Remove duplicates found in greater numbers
		// Else we would count, as an example, 2^4 and 4^2 as two different numbers
		if (a * a > N)
		{
			count += static_cast<long long>(N) - 1; // Add one for each since b=2...N
			continue;
		}

		const int nbPowers = static_cast<int>(N * std::ceil(std::log2(N) / std::log2(a))) + 1;
		std::vector<bool> isCounted(nbPowers, false);
		for (long long  aPow = a, power = 1; aPow <= N; power++, aPow *= a)
		{
			for (int i = 2; i <= N; i += 1)
			{
				if (!isCounted[i * power])
				{
					count++;
					isCounted[i* power] = true;
				}
			}
			isPower[aPow] = true;
		}
	}

	return count;
}

int main()
{
	int N;
	std::cin >> N;
	std::cout << Solve(N) << std::endl;
	
	return 0;
}