/// Problem 27: Quadratic primes
/// Find the product of the coefficients, a and b, for the quadratic expression n^2 + an + b 
/// that produces the maximum number of primes for consecutive values of n, starting with n = 0.
/// 42 <= N <= 2000
#include <iostream>
#include <vector>

static std::pair<int, int> Solve(int N)
{
	const int primeCount = N * N;
	std::vector<bool> isPrime(primeCount, true);
	isPrime[0] = isPrime[1] = false;
	// Sieve of Eratosthenes
	for (int i = 2; i * i < static_cast<int>(isPrime.size()); ++i)
	{
		if (isPrime[i])
		{
			for (int j = i * i; j < static_cast<int>(isPrime.size()); j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	// Check for primes
	int maxPrimes = 0;
	int maxA = 0;
	int maxB = 0;
	for (int a = -N; a <= N; ++a)
	{
		for (int b = -N; b <= N; ++b)
		{
			int n = 0;
			int sum = n * n + a * n + b;
			while (sum >= 0 && isPrime[sum])
			{
				++n;
				sum = n * n + a * n + b;
			}
			if (n > maxPrimes)
			{
				maxPrimes = n;
				maxA = a;
				maxB = b;
			}
		}
	}
	return { maxA, maxB };
}

int main()
{
	int N;
	std::cin >> N;
	const std::pair<int, int> ans = Solve(N);
	std::cout << ans.first << " " << ans.second << std::endl;
	return 0;
}