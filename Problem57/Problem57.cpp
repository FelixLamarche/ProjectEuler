// Problem 57: Square Root Convergents 
#include "../Utils/UnsignedBigInt.h"

#include <iostream>
#include <format>

#define LOGFMT(str, ...) do { std::cout << std::format(str, __VA_ARGS__); } while(0)
#define LOGFMT(str, ...) do {} while(0)

using u64 = unsigned long long;
using u32 = unsigned long;

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

static void SolveIteration(uBigInt& num1, uBigInt& denom1, u64 iterationCount)
{
	num1 = 1;
	denom1 = 2;
	for (u32 i = 0; i < iterationCount; ++i)
	{
		num1 += 2 * denom1;

		uBigInt temp = num1;
		num1 = denom1;
		denom1 = temp;
	}

	// Add 1
	num1 += denom1;
}

static u64 Solve()
{
	u32 numeratorDigitOverDenomDigit = 0;

	constexpr u32 iterations = 1000;
	for (u32 i = 0; i < iterations; ++i)
	{
		uBigInt num = 1;
		uBigInt denom = 2;
		SolveIteration(num, denom, i);

		LOGFMT("Iteration [{}]: {}/{}\n", i, num.ToString(), denom.ToString());

		const u64 numDigitsNum = NumberOfDigitsInNb(num);
		const u64 numDigitsDenom = NumberOfDigitsInNb(denom);
		if (numDigitsNum > numDigitsDenom)
			numeratorDigitOverDenomDigit++;
	}

	return numeratorDigitOverDenomDigit;
}

void main()
{
	const u64 sol = Solve();
	std::cout << "Problem 57 Solution: " << sol << std::endl;
}

