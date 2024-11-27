#include "Problem3.h"

#include <numeric>
#include <vector>

long long Problem3::Solve(long long n)
{
	long long remaining = n;
	long long square = static_cast<long long>(sqrtl(static_cast<long double>(n)));

	long long biggestPrime = n;

	long long div = 2;
	// We incrementaly go up the numbers, so only primes will be divisors
	// Since a composite number would be composed of smaller primes which
	// would have already divided the remaining portion, meaning only primes 
	// will trigger the (remaining % div == 0) boolean
	while (div < remaining && div <= square)
	{
		while (remaining % div == 0)
		{
			biggestPrime = div;
			remaining /= div;
		}
		div++;
	}

	return biggestPrime > remaining ? biggestPrime : remaining;
}
