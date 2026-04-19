// Problem 36 Double-base palindromes
// Find the sum of all numbers below 1'000'000 which is a palindrome in both base 10 and base 2
// e.g. 585 = 0b1001001001 (Do not include leading zeroes)

#include <iostream>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(false)

static int IntPower(const int nb, int exponent)
{
	int result = 1;
	while (exponent-- > 0) result *= nb;
	return result;
}

static bool IsNumberPalindromeBaseTen(const int num)
{
	int nbDigits = 0;
	int nb = num;
	while (nb > 0)
	{
		++nbDigits;
		nb /= 10;
	}

	bool isPalindrome = true;
	for (int digitIdx = 0; digitIdx < (nbDigits + 1) / 2; ++digitIdx)
	{
		const int highDigit = num / IntPower(10, nbDigits - 1 - digitIdx) % 10;
		const int lowDigit = (num / IntPower(10, digitIdx)) % 10;
		isPalindrome = isPalindrome && highDigit == lowDigit;

		if (!isPalindrome)
			break;
	}

	return isPalindrome;
}

static bool IsNumberPalindromeBaseTwo(const int num)
{
	int nbBits = 0;
	int nb = num;
	while (nb > 0)
	{
		nbBits++;
		nb = nb >> 1;
	}

	bool isPalindrome = true;
	for (int bitIdx = 0; bitIdx < (nbBits + 1) / 2; ++bitIdx)
	{
		const char highBit = (num & (1 << ((nbBits - 1) - bitIdx))) >> ((nbBits - 1) - bitIdx);
		const char lowBit = (num >> bitIdx) & 0b1;
		isPalindrome = isPalindrome && highBit == lowBit;
		if (!isPalindrome)
			break;
	}

	return isPalindrome;
}

static int Solve(const int upperBound)
{
	int sum = 0;

	for (int i = 1; i < upperBound; ++i)
	{
		if (IsNumberPalindromeBaseTwo(i) && IsNumberPalindromeBaseTen(i))
		{
			LOGF("Palindrome: %i\n", i);
			sum += i;
		}
	}

	return sum;
}

void main()
{
	constexpr int upperBound = 1'000'000;
	const int solution = Solve(upperBound);
	std::cout << "Solution: " << solution << std::endl;
}
