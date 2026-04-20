// Problem 38 Pandigital Multiples
// What is the largest pandigital 9-digit number that can be formed as the concatanated 
// product of an integer with (1,2, ..., n) where n > 1
// Where we seek a 9-digit number formed of the digits 1 through 9 without repeats

#include <iostream>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(false)

static int IntPower(const int nb, int exponent)
{
	int result = 1;
	while (exponent-- > 0) result *= nb;
	return result;
}

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

static int Solve()
{
	// Should be sufficient as we need to concatanate at least 2 numbers to form a number less than 1'000'000'000
	constexpr int upperBound = 10'000; 
	constexpr int pandigitalFlag = 0b1111111110;

	int biggestConcatanatedPandigital = 0;
	for (int i = 1; i < upperBound; ++i)
	{
		int digitsFlag = 0;
		int nbDigits = 0;
		int concatanatedNumber = 0;

		for (int n = 1; n < 10; ++n)
		{
			if (nbDigits >= 9)
				break;

			const int additionalNumber = i * n;
			const int additionalDigits = AddNumbersDigitsToFlag(digitsFlag, additionalNumber);

			concatanatedNumber *= IntPower(10, additionalDigits);
			concatanatedNumber += additionalNumber;
			nbDigits += additionalDigits;
		}

		const bool isPandigital = nbDigits == 9 && (digitsFlag & pandigitalFlag) == pandigitalFlag;

		if (isPandigital)
		{
			LOGF("%i: %i\n", i, concatanatedNumber);
			biggestConcatanatedPandigital = std::max(biggestConcatanatedPandigital, concatanatedNumber);
		}
	}

	return biggestConcatanatedPandigital;
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 38: " << solution << std::endl;
}

