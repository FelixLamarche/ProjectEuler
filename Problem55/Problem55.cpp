// Problem 55 Lychrel Numbers
// How many lychrel numbers below ten-thousand

#include "../Utils/Unsigned128.h"
#include "../Utils/UnsignedBigInt.h"
#include <format>
#include <iostream>
#include <set>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(0)
#define LOGFMT(str, ...) do { std::cout << std::format(str, __VA_ARGS__); } while(0)

using uint64 = unsigned long long;
using uint32 = unsigned long;

static uint64 NumberOfDigitsInNb(UnsignedBigInt nb)
{
	uint64 digitCount = 0;
	while (nb > 0)
	{
		digitCount++;
		nb /= 10;
	}
	return digitCount;
}

static UnsignedBigInt PowerOfTen(uint64 exp)
{
	UnsignedBigInt power = 1;
	for (uint64 i = 0; i < exp; ++i, power *= 10) {}
	return power;
}

static UnsignedBigInt GetDigitAtPosition(const UnsignedBigInt& nb, uint64 idx)
{
	const UnsignedBigInt powerOfTenDigits = PowerOfTen(static_cast<uint64>(idx + 1));
	const UnsignedBigInt powerOfTenDiv = powerOfTenDigits / 10;
	return (nb % powerOfTenDigits) / powerOfTenDiv;
}

static bool IsNumberPalindrome(const UnsignedBigInt& nb)
{
	const uint64 digits = NumberOfDigitsInNb(nb);
	if (digits <= 1)
		return false;

	for (uint64 idx = 0; idx < digits / 2; ++idx)
	{
		const UnsignedBigInt smallerDigit = GetDigitAtPosition(nb, idx);
		const UnsignedBigInt biggerDigit = GetDigitAtPosition(nb, digits - idx - 1);

		if (smallerDigit != biggerDigit)
			return false;
	}

	return true;
}

static UnsignedBigInt ReverseDigitsNumber(const UnsignedBigInt& nb)
{
	const uint64 digits = NumberOfDigitsInNb(nb);
	UnsignedBigInt reversedNb = 0;
	for (uint64 idx = 0; idx < digits; ++idx)
	{
		reversedNb *= 10;
		reversedNb += GetDigitAtPosition(nb, idx);
	}
	return reversedNb;
}

static uint64 Solve()
{
	constexpr uint64 upperLimit = 10'000;

	std::set<uint32> lychrelNumbers;

	uint64 lychrelCount = 0;
	uint32 bigIntLimitForCache = 1'000'000'000;

	for (uint64 baseNb = 1; baseNb < upperLimit; ++baseNb)
	{
		UnsignedBigInt nb = baseNb;
		constexpr uint64 iterationMax = 50;
		bool isLychrelNb = true;
		for (uint64 i = 0; i < iterationMax; ++i)
		{
			if (nb < bigIntLimitForCache)
			{
				uint32 nbSmall = static_cast<uint32>(nb);
				if (lychrelNumbers.contains(nbSmall))
				{
					isLychrelNb = false;
					break;
				}
			}
			//LOGFMT("ITERATION:  baseNb:{}, nb:{}, i:{}\n", baseNb, nb.ToString().c_str(), i);

			nb += ReverseDigitsNumber(nb);
			if (IsNumberPalindrome(nb))
			{
				isLychrelNb = false;
				break;
			}
		}

		if (isLychrelNb)
		{
			LOGFMT("LYCHRLEL:    baseNb:{}, nb: {}\n", baseNb, nb.ToString().c_str());
			lychrelCount++;
		}
	}

	return lychrelCount;
}

int main()
{
	const uint64 solution = Solve();
	// Solution is correct, but the computed numbers overflow, oh well
	std::cout << "Problem 55 Solution: " << solution << std::endl;

	return 0;
}
