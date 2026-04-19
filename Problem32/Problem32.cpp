// Problem 32 Pandigital Products:
// Find the sum of all products whose multiplicand/multiplier/product identity can be written as 1 through 9 pandigital.

#include <iostream>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(false)

static int AddNumbersDigitsToFlag(int& outDigitsFlag, int num)
{
	int digitsAdded = 0;
	while (num > 0)
	{
		outDigitsFlag = outDigitsFlag | (1 << (num % 10));
		num /= 10;
		++digitsAdded;
	}
	return digitsAdded;
}

static bool IsTrioPandigital(int a, int b, int c)
{
	constexpr int pandigitalFlag = 0b1111111110;
	int digitsFlag = 0;
	int digitsAdded = 0;
	
	digitsAdded += AddNumbersDigitsToFlag(digitsFlag, a);
	digitsAdded += AddNumbersDigitsToFlag(digitsFlag, b);
	digitsAdded += AddNumbersDigitsToFlag(digitsFlag, c);

	return digitsAdded == 9 && (digitsFlag & pandigitalFlag) == pandigitalFlag;
}

static int Solve()
{
	constexpr int maxProduct = 100'000'000'0;

	int sumOfPandigitalProducts = 0;
	for (int product = 1; product < maxProduct; ++product)
	{
		const int maxMultiplicand = std::sqrt(product);
		for (int multiplicand = 1; multiplicand < maxMultiplicand; ++multiplicand)
		{
			const int multiplier = product / multiplicand;
			if (multiplicand * multiplier != product)
				continue;

			if (IsTrioPandigital(multiplicand, multiplier, product))
			{
				LOGF("Pandigital: %i x %i = %i\n", multiplicand, multiplier, product);
				sumOfPandigitalProducts += product;
				break;
			}
		}
	}
	return sumOfPandigitalProducts;
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 32 Solution: " << solution << std::endl;
}