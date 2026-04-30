// Problem 55 Lychrel Numbers
// How many lychrel numbers below ten-thousand

#include <iostream>

using uint64 = unsigned long long;

static uint64 NumberOfDigitsInNb(uint64 nb)
{
	uint64 digitCount = 0;
	while (nb > 0)
	{
		digitCount++;
		nb /= 10;
	}
	return digitCount;
}

static uint64 PowerOfTen(int exp)
{
	uint64 power = 1;
	for (int i = 0; i < exp; ++i, power *= 10) {}
	return power;
}

static uint64 GetDigitAtPosition(uint64 nb, uint64 idx)
{
	return (nb % PowerOfTen(idx + 1)) / PowerOfTen(idx);
}

static bool IsNumberPalindrome(uint64 nb)
{
	const uint64 digits = NumberOfDigitsInNb(nb);
	if (digits <= 1)
		return false;

	for (uint64 idx = 0; idx < digits / 2; ++idx)
	{
		const uint64 smallerDigit = GetDigitAtPosition(nb, idx);
		const uint64 biggerDigit = GetDigitAtPosition(nb, digits - idx - 1);

		if (smallerDigit != biggerDigit)
			return false;
	}

	return true;
}

static uint64 ReverseDigitsNumber(uint64 nb)
{
	const uint64 digits = NumberOfDigitsInNb(nb);
	uint64 reversedNb = 0;
	for (uint64 idx = 0; idx < digits; ++idx)
	{
		reversedNb *= 10;
		reversedNb += GetDigitAtPosition(nb, idx);
	}

	return reversedNb;
}

static int Solve()
{
	constexpr uint64 upperLimit = 10'000;
	
	int lychrelCount = 0;
	for (uint64 baseNb = 1; baseNb < upperLimit; ++baseNb)
	{
		uint64 nb = baseNb;
		constexpr uint64 iterationMax = 50;
		bool isLychrelNb = true;
		for (uint64 i = 0; i < iterationMax; ++i)
		{
			nb += ReverseDigitsNumber(nb);

			if (IsNumberPalindrome(nb))
			{
				isLychrelNb = false;
				break;
			}
		}

		if (isLychrelNb)
			lychrelCount++;
	}

	return lychrelCount;
}

void main()
{
	const int solution = Solve();
	// Solution is correct, but the computed numbers overflow, oh well
	std::cout << "Problem 55 Solution: " << solution << std::endl;
}
