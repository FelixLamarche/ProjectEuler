// Problem 47 Distinct Prime Factors
// The first two consecutive numbers to have two distinct prime factors are:
// 14 = 2 x 7
// 15 = 3 x 5
// The first three with three distint prime factors are:
// 644 = 2^2 x 7 x 23
// 645 = 3 x 5 x 43
// 646 = 2 x 17 x 19
// What are the first four consecutive numbers which have four distinct prime factors?
// What is the first number of this sequence?

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(0)

static int GetPrimeFactorCount(const std::vector<int>& primes, int nb)
{
	int primeFactorCount = 0;

	for (int prime : primes)
	{
		if (nb % prime == 0)
			++primeFactorCount;
	}
	return primeFactorCount;
}

static int Solve()
{
	constexpr int sieveCount = 1'000'000;
	std::vector<bool> primeSieve(sieveCount, true);
	primeSieve[0] = false;
	primeSieve[1] = false;

	for (int n = 2; n < sieveCount / 2; ++n)
	{
		for (int multiple = 2 * n; multiple < sieveCount; multiple += n)
		{
			primeSieve[multiple] = false;
		}
	}

	const int primeCount = std::count_if(primeSieve.begin(), primeSieve.end(), [](const bool val) { return val; });

	std::vector<int> primes;
	primes.reserve(primeCount);
	for (int nb = 0; nb < sieveCount; ++nb)
	{
		if (primeSieve[nb])
			primes.push_back(nb);
	}
	
	constexpr int streakGoal = 4;
	constexpr int primeFactorCountGoal = 4;

	int nb = 2;
	int streak = 0;
	for (; nb < sieveCount; ++nb)
	{
		const int primeFactorCount = GetPrimeFactorCount(primes, nb);
		if (primeFactorCount == primeFactorCountGoal)
			streak++;
		else
			streak = 0;

		if (streak >= streakGoal)
			break;
	}

	return nb - (streakGoal - 1);
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 47 Solution: " << solution << std::endl;
}
