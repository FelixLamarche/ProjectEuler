// Problem 37 Truncatable Primes
// Find the sum of the 11 primes which are primes when truncated from left-to-right and right-to-left
// Where 3797 is a truncatable prime, because 3797, 797, 97, 7 are also prime

#include <iostream>
#include <vector>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(false)

static int IntPower(const int nb, int exponent)
{
	int result = 1;
	while (exponent-- > 0) result *= nb;
	return result;
}

static int Solve()
{
	constexpr int upperBound = 1'000'000;
	std::vector<bool> primeSieve(upperBound + 1, true);
	primeSieve[0] = false;
	primeSieve[1] = false;

	for (int i = 2; i < std::sqrt(primeSieve.size()); ++i)
	{
		for (int product = 2 * i; product < primeSieve.size(); product += i)
			primeSieve[product] = false;
	}

	int sum = 0;
	for (int i = 10; i < upperBound; ++i)
	{
		if (!primeSieve[i]) continue;

		int nbDigits = 0;
		int nb = i;
		while (nb > 0)
		{
			++nbDigits;
			nb /= 10;
		}

		bool isTruncatablePrime = true;
		int leftToRightNum = i;
		int rightToLeftNum = i;
		for (int digit = 1; digit < nbDigits; ++digit)
		{
			leftToRightNum /= 10;
			isTruncatablePrime = isTruncatablePrime && primeSieve[leftToRightNum];
			if (!isTruncatablePrime) break;

			rightToLeftNum = rightToLeftNum % IntPower(10, nbDigits - digit);
			isTruncatablePrime = isTruncatablePrime && primeSieve[rightToLeftNum];
			if (!isTruncatablePrime) break;
		}

		if (isTruncatablePrime)
		{
			LOGF("Truncatable Prime: %i\n", i);
			sum += i;
		}
	}

	return sum;
}

void main()
{
	const int solution = Solve();
	std::cout << "Solution: " << solution << std::endl;
}