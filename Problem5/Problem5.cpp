#include "Problem5.h"

#include <numeric>

long long Problem5::Solve(int n)
{
	long long smallest = 1;
	for (int i = 2; i <= n; i++)
	{
		if (IsPrime(i))
		{
			// Account for powers of primes
			for (int powers = i; powers <= n; powers *= i)
			{
				smallest *= i;
			}
		}
	}
	return smallest;
}

bool Problem5::IsPrime(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}