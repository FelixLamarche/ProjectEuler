// Problem 60: Prime Pair Sets

#include <format>
#include <iostream>
#include <numeric>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

static bool IsPrime(const u64 nb)
{
	if (nb <= 1)
		return false;
	if (nb == 2)
		return true;

	const u64 maxNb = ceil(sqrt(nb));
	for (u64 divider = 2; divider <= maxNb; ++divider)
	{
		if (nb % divider == 0)
			return false;
	}
	return true;
}

static u64 Power10(u64 exp)
{
	u64 power = 1;
	while (exp--)
		power *= 10;
	return power;
}

static u64 ConcatenateNumbers(const u64 nb1, const u64 nb2)
{
	const u32 nb2Digits = ceil(log10(nb2));
	return nb1 * Power10(nb2Digits) + nb2;
}

static bool AreConcatanatedPrimesPrime(const u64 prime1, const u64 prime2)
{
	return IsPrime(ConcatenateNumbers(prime1, prime2)) && IsPrime(ConcatenateNumbers(prime2, prime1));
}

static u64 Solve()
{
	constexpr u32 nbPrimesInSet = 5;

	std::vector<u64> primes;
	u64 nb = 1;

	std::vector<u64> primesAttempt(nbPrimesInSet);
	bool foundSol = false;
	while (!foundSol)
	{
		nb++;

		const bool isPrime = IsPrime(nb);
		if (!isPrime)
			continue;

		primes.push_back(nb);

		if (nbPrimesInSet > primes.size())
			continue;

		// The last prime added will be in the found set, so consider it the last member of the set
		primesAttempt[primesAttempt.size() - 1] = primes.back();

		for (int i1 = 0; i1 < primes.size() - nbPrimesInSet + 1; ++i1)
		{
			primesAttempt[0] = primes[i1];

			if (!AreConcatanatedPrimesPrime(primesAttempt[0], primesAttempt[4]))
				continue;

			for (int i2 = i1 + 1; i2 < primes.size() - nbPrimesInSet + 2; ++i2)
			{
				primesAttempt[1] = primes[i2];

				if (!AreConcatanatedPrimesPrime(primesAttempt[1], primesAttempt[0]))
					continue;

				if (!AreConcatanatedPrimesPrime(primesAttempt[1], primesAttempt[4]))
					continue;

				for (int i3 = i2 + 1; i3 < primes.size() - nbPrimesInSet + 3; ++i3)
				{
					primesAttempt[2] = primes[i3];

					if (!AreConcatanatedPrimesPrime(primesAttempt[2], primesAttempt[0]))
						continue;

					if (!AreConcatanatedPrimesPrime(primesAttempt[2], primesAttempt[1]))
						continue;

					if (!AreConcatanatedPrimesPrime(primesAttempt[2], primesAttempt[4]))
						continue;

					for (int i4 = i3 + 1; i4 < primes.size() - nbPrimesInSet + 4; ++i4)
					{
						primesAttempt[3] = primes[i4];

						if (!AreConcatanatedPrimesPrime(primesAttempt[3], primesAttempt[0]))
							continue;

						if (!AreConcatanatedPrimesPrime(primesAttempt[3], primesAttempt[1]))
							continue;

						if (!AreConcatanatedPrimesPrime(primesAttempt[3], primesAttempt[2]))
							continue;

						if (!AreConcatanatedPrimesPrime(primesAttempt[3], primesAttempt[4]))
							continue;

						foundSol = true;
						break;
					}
					if (foundSol)
						break;
				}
				if (foundSol)
					break;
			}
			if (foundSol)
				break;
		}
	}

	std::cout << "Solution:\n";
	for (u64 prime : primesAttempt)
	{
		std::cout << prime << "\n";
	}
	std::cout << std::endl;

	const u64 solutionSum = std::accumulate(primesAttempt.begin(), primesAttempt.end(), 0);
	return solutionSum;
}

void main()
{
	const u64 sol = Solve();
	std::cout << "Solution 60: " << sol << std::endl;
}