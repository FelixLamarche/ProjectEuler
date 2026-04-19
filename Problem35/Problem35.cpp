// Problem 35 Circular Primes
// A prime is circular if all rotations of its digits are also primes (e.g. 197 is a circular prime, because 197, 971, 719 are primes)

// How many such primes exist below 1'000'000

#include <iostream>
#include <vector>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(false)

static int GetNumDigitsOfNumber(int num)
{
	int digits = 0;
	while (num > 0)
	{
		digits += 1;
		num /= 10;
	}
	return digits;
}

static int Solve(const int upperBound)
{
	std::vector<bool> primeSieve(upperBound + 1, true);
	primeSieve[0] = false;
	primeSieve[1] = false;
	for (int i = 2; i < std::sqrt(primeSieve.size()); ++i)
	{
		for (int product = 2 * i; product < primeSieve.size(); product += i)
			primeSieve[product] = false;
	}

	int count = 0;
	for (int i = 2; i < upperBound; ++i)
	{
		int num = i;
		const int numDigits = GetNumDigitsOfNumber(num);
		int magnitude = 1;
		for (int i = 1; i < numDigits; ++i)
			magnitude *= 10;

		bool isPrime = true;
		for (int i = 0; i < numDigits; ++i)
		{
			const int delta = (num % 10) * magnitude;
			num = (num / 10) + delta;
			if (!primeSieve[num])
			{
				isPrime = false;
				break;
			}
		}

		if (isPrime)
		{
			LOGF("Circular Prime: %i\n", i);
			++count;
		}
	}
	return count;
}

void main()
{
	const int upperBound = 1'000'000;
	const int solution = Solve(upperBound);
	std::cout << std::endl << "Problem 35 Solution: " << solution << std::endl;
}