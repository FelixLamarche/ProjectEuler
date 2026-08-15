// Problem 73: Counting Fractions in a Range

#include <format>
#include <iostream>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;

static bool AreCoprime(u32 a, u32 b)
{
	const u32 max = std::max(a, b);
	const u32 min = std::min(a, b);
	for (u32 divider = 2; divider <= min; ++divider)
	{
		if (min % divider == 0 && max % divider == 0)
			return false;
	}
	return true;
}

static u32 Solve(u32 upperBound, u32 minFractionNumerator, u32 minFractionDenominator, u32 maxFractionNumerator, u32 maxFractionDenominator)
{
	// Returns the numerator of the proper fraction which is directly before the fraction of 
	// numeratorGoal / denominatorGoal, if all proper fractions n / d, where d <= upperBound
	// then are ordered by their size

	const double minFraction = static_cast<double>(minFractionNumerator) / minFractionDenominator;
	const double maxFraction = static_cast<double>(maxFractionNumerator) / maxFractionDenominator;

	u32 properFractionCount = 0;
	for (u32 denominator = 2; denominator <= upperBound; ++denominator)
	{
		for (u32 numerator = 1; numerator < denominator; ++numerator)
		{
			const double fractionValue = static_cast<double>(numerator) / denominator;

			if (fractionValue >= maxFraction)
				break;

			if (fractionValue <= minFraction)
				continue;

			if (AreCoprime(numerator, denominator))
			{
				properFractionCount++;
			}
		}
	}

	return properFractionCount;
}

int main()
{
	constexpr u32 upperBound = 12'000;
	constexpr u32 minFractionNumerator = 1;
	constexpr u32 minFractionDenominator = 3;
	constexpr u32 maxFractionNumerator = 1;
	constexpr u32 maxFractionDenominator = 2;

	const u32 sol = Solve(upperBound, minFractionNumerator, minFractionDenominator, maxFractionNumerator, maxFractionDenominator);
	std::cout << "Solution 73: " << sol << std::endl;

	return 0;
}