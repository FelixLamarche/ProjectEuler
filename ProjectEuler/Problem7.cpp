#include "Problem7.h"

#include <vector>

int Problem7::Solve(int n)
{
	// The 10001st prime is 104743
	// So all prime 'n' will be below this
	const int limit = 104743;
	std::vector<bool> sieve;
	sieve.insert(sieve.begin(), limit, true);
	sieve[0] = false;
	sieve[1] = false;

	for (size_t i = 2; i < sieve.size(); i++)
	{
		for (size_t j = 2; j * i < sieve.size(); j++)
		{
			sieve[j * i] = false;
		}
	}

	int nb = 0;
	int lastPrime = 0;
	for (size_t i = 0; nb < n && i < sieve.size(); i++)
	{
		if (sieve[i])
		{
			nb++;
			lastPrime = static_cast<int>(i);
		}
	}

	return lastPrime;
}
