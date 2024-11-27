#include "Problem10.h"
#include "../ProjectEuler/Sieve.h"

#include <map>
#include <iterator>

long long Problem10::Solve(int N)
{
	typename typedef std::map<int, long long> Cache;
	static Utils::Sieve sieve(N + 1);
	static Cache primeSums = Cache { {0, 0} };

	if (N > sieve.Size())
	{
		sieve = Utils::Sieve(N + 1);
	}

	Cache::const_iterator it = primeSums.lower_bound(N);

	long long sum;
	int i;
	if (it == primeSums.begin())
	{
		sum = 0;
		i = 2;
	}
	else
	{
		it--;
		i = it->first + 1;
		sum = it->second;
	}
	
	for (; i <= N; i++)
	{
		if (sieve.IsPrime(i))
		{
			sum += i;
			primeSums[i] = sum;
		}
	}
	return sum;
}