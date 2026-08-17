// Problem 80: Square Root Digital Expansion

#include "../Utils/UnsignedBigInt.h"
#include <format>
#include <iostream>
#include <string>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;

static u64 DigitalSum(UnsignedBigInt nb)
{
	u64 digitalSum = 0;
	while (nb > 0)
	{
		digitalSum += static_cast<u64>(nb % 10);
		nb /= 10;
	}
	return digitalSum;
}

static int Solve(const int upperBound, const int digitsCount)
{
	int digitsSumBelowBound = 0;
	for (int nb = 1; nb <= upperBound; ++nb)
	{
		const int nbSqrt = std::sqrt(nb);
		if (nbSqrt * nbSqrt == nb)
		{
			continue; // rational square root, skip
		}

		const int significantDigitsToAdd = digitsCount - std::ceil(std::log10(nbSqrt + 1));
		// Make the number big enough as an integer containing the necessary digit precision
		uBigInt bigNb = nb;
		for (int i = 0; i < significantDigitsToAdd; ++i)
			bigNb *= 100;

		uBigInt bigSqrtNb = nbSqrt;
		for (int i = 0; i < significantDigitsToAdd; ++i)
			bigSqrtNb *= 10;

		uBigInt bigSqrtNb2 = bigSqrtNb;
		
		uBigInt* prevBigSqrt = &bigSqrtNb;
		uBigInt* nextBigSqrt = &bigSqrtNb2;

		int testI = 0;
		do
		{
			*nextBigSqrt = bigNb / *prevBigSqrt;
			*nextBigSqrt = (*nextBigSqrt + *prevBigSqrt) / 2;

			uBigInt* temp = nextBigSqrt;
			nextBigSqrt = prevBigSqrt;
			prevBigSqrt = temp;

			//LOGFMT("i: {} : {}\n", testI, nextBigSqrt->ToString());
			testI++;
		} while (bigSqrtNb != bigSqrtNb2);

		u64 digitsSum = DigitalSum(bigSqrtNb);
		digitsSumBelowBound += digitsSum;

		std::cout << nb << ": " << digitsSum << std::endl;
	}

	return digitsSumBelowBound;;
}

int main()
{
	constexpr int upperBound = 100;
	constexpr int digitsCount = 100;
	const int sol = Solve(upperBound, digitsCount);
	std::cout << "Solution 80: " << sol << std::endl;

	return 0;
}