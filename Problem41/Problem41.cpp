// Problem 41 Pandigital Prime
// an n-digit number is pandigital if it makes use of all digits from 1 to n exactly once
// What is the largest n-digit pandigital prime?

#include <iostream>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(false)

static int AddNumbersDigitsToFlag(int& outDigitsFlag, int num)
{
	int digitsCount = 0;
	while (num > 0)
	{
		outDigitsFlag = outDigitsFlag | (1 << (num % 10));
		num /= 10;
		++digitsCount;
	}
	return digitsCount;
}

static bool IsPandigital(int nb)
{
	int digitsFlag = 0;
	int digitsCount = AddNumbersDigitsToFlag(digitsFlag, nb);

	digitsFlag = digitsFlag >> 1; // remove leading zero digit
	
	int nbDigits = 0;
	while (digitsFlag & 1)
	{
		++nbDigits;
		digitsFlag = digitsFlag >> 1;
	}

	return nbDigits == digitsCount;
}


static int Solve()
{
	constexpr int upperBoundPrime = 1'000'000'000;
	bool* primeSieve = new bool[upperBoundPrime];
	primeSieve[0] = false;
	primeSieve[1] = false;

	for (int nb = 2; nb < upperBoundPrime; ++nb)
	{
		if (!primeSieve)
			continue;

		for (int multiple = 2 * nb; multiple < upperBoundPrime; multiple += nb)
		{
			primeSieve[multiple] = false;
		}
	}

	int largestPandigitalPrime = 0;
	for (int nb = 0; nb < upperBoundPrime; ++nb)
	{
		if (!primeSieve[nb])
			continue;

		if (IsPandigital(nb))
			largestPandigitalPrime = nb;
	}

	delete[] primeSieve;
	return largestPandigitalPrime;
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 41 Solution: " << solution << std::endl;
}