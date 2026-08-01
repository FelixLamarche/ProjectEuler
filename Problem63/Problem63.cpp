// Problem 63 : Powerful Digit Counts

#include "../Utils/UnsignedBigInt.h"

#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned long;
using u64 = unsigned long long;

static uBigInt Power(const uBigInt nb, const u64 exp)
{
	uBigInt sol = nb;
	for (int i = 1; i < exp; ++i)
		sol *= nb;
	return sol;
}

static u32 DigitsCount(uBigInt n)
{
	u32 digits = 0;
	while (n > 0)
	{
		digits++;
		n /= 10;
	}
	return digits;
}

static u64 Solve()
{
	u64 solCount = 0;

	const u64 maxExponent = 100;
	for (u64 exponent = 1; exponent < maxExponent; exponent++)
	{
		for (uBigInt nb = 1; ; nb++)
		{
			const uBigInt power = Power(nb, exponent);
			const u32 digitsCount = DigitsCount(power);


			if (digitsCount == exponent)
			{

				std::cout << nb.ToString() << "^" << exponent << " = " << power.ToString() << std::endl;
				solCount++;
			}
			else if (digitsCount > exponent)
				break;
		}
	}

	return solCount;
}

void main()
{
	const u64 sol = Solve();
	std::cout << "Solution 63: " << sol << std::endl;
}
