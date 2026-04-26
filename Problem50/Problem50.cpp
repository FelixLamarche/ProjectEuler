// Problem 50 Consecutive Prime Sum
// Which prime betlow one-million can be written as the sum of the most consecutive primes?

#include <algorithm>
#include <iostream>
#include <vector>

static int Solve()
{
	constexpr int nbsCount = 1'000'000;
	std::vector<bool> primeSieve(nbsCount, true);
	primeSieve[0] = false;
	primeSieve[1] = false;

	for (int n = 2; n < nbsCount; ++n)
	{
		for (int multiple = 2 * n; multiple < nbsCount; multiple += n)
		{
			primeSieve[multiple] = false;
		}
	}

	const int primeCount = std::count_if(primeSieve.begin(), primeSieve.end(), [](bool val) { return val; });

	std::vector<int> primes;
	primes.reserve(primeCount);
	for (int nb = 0; nb < nbsCount; ++nb)
	{
		if (primeSieve[nb])
			primes.push_back(nb);
	}

	int primeSummedWithMostConsecutivePrimes = 0;
	int biggestSumCount = 0;

	for (int summedPrimeIdx = 0; summedPrimeIdx < primeCount; ++summedPrimeIdx)
	{
		const int summedPrime = primes[summedPrimeIdx];
		for (int startPrimeIdx = 0; startPrimeIdx < summedPrimeIdx; ++startPrimeIdx)
		{
			int sum = 0;
			int primeCount;
			for (primeCount = 0; primeCount + startPrimeIdx < summedPrimeIdx; ++primeCount)
			{
				if (sum >= summedPrime)
					break;

				sum += primes[primeCount + startPrimeIdx];
			}

			if (sum == summedPrime && primeCount > biggestSumCount)
			{
				primeSummedWithMostConsecutivePrimes = summedPrime;
				biggestSumCount = primeCount;
			}
		}
	}

	return primeSummedWithMostConsecutivePrimes;
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 50 Solution: " << solution << std::endl;
}