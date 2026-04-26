// Problem 51 Prime Digit Replacements

#include <iostream>
#include <vector>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(0)

static int DigitMask(int nb, const int digit)
{
	int nbMagnitude = 1;
	while (nbMagnitude * 10 <= nb) { nbMagnitude *= 10; }

	int digitMask = 0;

	while (nb > 0)
	{
		int largestDigit = nb / nbMagnitude;

		digitMask *= 10;
		if (largestDigit == digit)
			digitMask += digit;

		nb = nb % nbMagnitude;
		nbMagnitude /= 10;
	}

	return digitMask;
}

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

	// Keep track of the primes using the digit 1 as the standin for the changing digit
	std::vector<int> primeCounts(nbsCount / 5, 0);

	constexpr int swappedDigit = 1;

	for (int nb = 0; nb < primeCounts.size(); ++nb)
	{
		int swapDigitMask = DigitMask(nb, swappedDigit);
		if (swapDigitMask == 0)
			continue;

		// Swap all instances of the digit in the number to the specified digit
		for (int digit = 0; digit < 9; ++digit)
		{
			int primeCandidate = nb + (digit * swapDigitMask);

			if (primeSieve[primeCandidate])
			{
				primeCounts[nb]++;
			}
		}
	}

	for (int nb = 0; nb < primeCounts.size(); ++nb)
	{
		if (primeCounts[nb] >= 8)
		{
			LOGF("%i\n", nb);
		}
	}

	return 0;
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 51 Solution: " << solution << std::endl;
}