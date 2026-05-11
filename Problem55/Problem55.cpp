// Problem 55 Lychrel Numbers
// How many lychrel numbers below ten-thousand

#include "../Utils/Unsigned128.h"
#include <format>
#include <iostream>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(0)
#define LOGFMT(str, ...) do { std::cout << std::format(str, __VA_ARGS__); } while(0)

using uint64 = unsigned long long;
using uint32 = unsigned long;

static uint64 NumberOfDigitsInNb(uint128 nb)
{
	uint64 digitCount = 0;
	while (nb > 0)
	{
		digitCount++;
		nb /= 10;
	}
	return digitCount;
}

static uint128 PowerOfTen(uint64 exp)
{
	uint128 power = 1;
	for (uint64 i = 0; i < exp; ++i, power *= 10) {}
	return power;
}

static uint128 GetDigitAtPosition(const uint128& nb, uint64 idx)
{
	const uint128 powerOfTenDigits = PowerOfTen(static_cast<uint64>(idx + 1));
	const uint128 powerOfTenDiv = powerOfTenDigits / 10;
	return (nb % powerOfTenDigits) / powerOfTenDiv;
}

static bool IsNumberPalindrome(const uint128& nb)
{
	const uint64 digits = NumberOfDigitsInNb(nb);
	if (digits <= 1)
		return false;

	for (uint64 idx = 0; idx < digits / 2; ++idx)
	{
		const uint128 smallerDigit = GetDigitAtPosition(nb, idx);
		const uint128 biggerDigit = GetDigitAtPosition(nb, digits - idx - 1);

		if (smallerDigit != biggerDigit)
			return false;
	}

	return true;
}

static uint128 ReverseDigitsNumber(const uint128& nb)
{
	const uint64 digits = NumberOfDigitsInNb(nb);
	uint128 reversedNb = 0;
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
		uint128 nb = baseNb;
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
		{
			uint64 nb64 = static_cast<uint64>(nb);
			LOGFMT("LYCHRLEL:    baseNb:{}, nb: {}\n", baseNb, nb.ToString().c_str());
			lychrelCount++;
		}
	}

	return lychrelCount;
}

void main()
{
	const uint64 solution = Solve();
	// Solution is correct, but the computed numbers overflow, oh well
	std::cout << "Problem 55 Solution: " << solution << std::endl;
}
