// Problem 87: Prime Power Triples

#include <algorithm>
#include <format>
#include <iostream>
#include <set>
#include <vector>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

// Returns how many numbers below upperBound which can be expressed as p^2 + q^3 + r^4, where p,q,r are prime numbers
static u64 Solve(const u64 upperBound)
{
	std::vector<u64> primes;

	// Get all relevant primes
	{
		const u64 primeUpperBound = std::ceil(std::sqrt(upperBound));
		std::vector<bool> primeSieve(primeUpperBound + 1, true);
		primeSieve[0] = false;
		primeSieve[1] = false;

		for (u64 nb = 2; nb < primeSieve.size(); ++nb)
		{
			if (!primeSieve[nb])
				continue;
			for (u64 multiple = 2 * nb; multiple < primeSieve.size(); multiple += nb)
			{
				primeSieve[multiple] = false;
			}
		}

		const u64 primeCount = std::count(primeSieve.begin(), primeSieve.end(), true);
		primes.reserve(primeCount);
		for (u64 nb = 0; nb < primeSieve.size(); ++nb)
		{
			if (primeSieve[nb])
				primes.push_back(nb);
		}
	}

	std::set<u64> sumsOfPrimePowers;
	for (const u64 primeToFourthPower : primes)
	{
		const u64 primeFourthPower = primeToFourthPower * primeToFourthPower * primeToFourthPower * primeToFourthPower;
		if (primeFourthPower >= upperBound)
			break;
		
		for (const u64 primeToCube : primes)
		{
			const u64 primeCube = primeToCube * primeToCube * primeToCube;

			const u64 primeSumToCube = primeFourthPower + primeCube;
			if (primeSumToCube > upperBound)
				break;

			for (const u64 primeToSquare : primes)
			{
				const u64 primeSquare = primeToSquare * primeToSquare;
				const u64 sumOfPrimePowers = primeSumToCube + primeSquare;
				if (sumOfPrimePowers > upperBound)
					break;

				sumsOfPrimePowers.insert(sumOfPrimePowers);
			}
		}
	}

	return sumsOfPrimePowers.size();
}

int main()
{
	const u64 upperBound = 50'000'000;
	const u64 sol = Solve(upperBound);
	std::cout << "Solution 87: " << sol << std::endl;

	return 0;
}
