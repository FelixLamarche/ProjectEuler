// Problem 30: Digit fifth powers
// Find the sum of all the numbers that can be written as the sum of fifth powers of their digits

// Manually calculated the upper bound = 6 * 9^5 = 354294, 7 digits would be 7 * 9^5 = 413343, so we can stop at 354294

#include <iostream>
#include <format>

#define LOG(x) std::cout << x << std::endl;

static constexpr int FifthPower(int n)
{
	return n * n * n * n * n;
}

static int SumOfDigitsToFifthPower(int n)
{
	int sum = 0;
	while (n > 0)
	{
		sum += FifthPower(n % 10);
		n /= 10;
	}
	return sum;
}

static void Solve()
{
	constexpr int maximumDigitAmount = 6;
	constexpr int upperBound = maximumDigitAmount * FifthPower(9);

	int sumOfMatches = 0;
	for (int i = 2; i <= upperBound; ++i)
	{
		const int sum = SumOfDigitsToFifthPower(i);
		if (sum == i)
		{
			LOG(std::format("Sum of Digits to Fifth Power Found: {}", sum));
			sumOfMatches += sum;
		}
	}
	
	std::cout << "Solution Problem 30: " << sumOfMatches << std::endl;
}

int main()
{
	Solve();
	return 0;
}