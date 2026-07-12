// Problem 56 Powerful Digit Sum

#include "../Utils/UnsignedBigInt.h"
#include <format>
#include <iostream>
#include <set>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(0)
#define LOGFMT(str, ...) do { std::cout << std::format(str, __VA_ARGS__); } while(0)

using uint64 = unsigned long long;
using uint32 = unsigned long;

static uint64 DigitalSum(UnsignedBigInt nb)
{
	uint64 digitalSum = 0;
	while (nb > 0)
	{
		digitalSum += static_cast<uint32>(nb % 10);
		nb /= 10;
	}
	return digitalSum;
}

static uint64 Solve()
{
	constexpr uint64 upperLimit = 100;

	uint64 biggestDigitalSum = 0;
	uint64 biggestBaseNbDigitalSum = 0;
	uint64 biggestExponentDigitalSum = 0;

	for (uint64 baseNb = 1; baseNb < upperLimit; ++baseNb)
	{
		UnsignedBigInt nb = 1;

		for (uint64 exponent = 1; exponent < upperLimit; ++exponent)
		{
			nb *= baseNb;

			//LOGFMT("ITERATION:  baseNb:{}, nb:{}, i:{}\n", baseNb, nb.ToString().c_str(), i);

			const uint64 digitsSum = DigitalSum(nb);

			if (digitsSum > biggestDigitalSum)
			{
				biggestDigitalSum = digitsSum;
				biggestBaseNbDigitalSum = baseNb;
				biggestExponentDigitalSum = exponent;

				LOGFMT("Biggest Digital Sum: {}:  Nb: {}^{}:   {}\n", digitsSum, baseNb, exponent, nb.ToString());
			}

		}

	}

	return biggestDigitalSum;
}

int main()
{
	const uint64 solution = Solve();
	std::cout << "Problem 56 Solution: " << solution << std::endl;

	return 0;
}
