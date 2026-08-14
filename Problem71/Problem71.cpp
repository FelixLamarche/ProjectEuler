// Problem 71: Ordered Fractions

#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

static void Solve(u32 upperBound, u32 numeratorGoal, u32 denominatorGoal, u32& bestNumerator, u32& bestDenominator)
{
	// Returns the numerator of the proper fraction which is directly before the fraction of 
	// numeratorGoal / denominatorGoal, if all proper fractions n / d, where d <= upperBound
	// then are ordered by their size

	const double fractionGoal = static_cast<double>(numeratorGoal) / denominatorGoal;

	double closestFraction = 0;

	for (u32 denominator = 2; denominator <= upperBound; ++denominator)
	{
		for (u32 numerator = 1; numerator < denominator; ++numerator)
		{
			const double fractionValue = static_cast<double>(numerator) / denominator;

			if (fractionValue >= fractionGoal)
				break;

			if (fractionValue > closestFraction)
			{
				closestFraction = fractionValue;
				bestNumerator = numerator;
				bestDenominator = denominator;
			}
		}
	}
}

int main()
{
	constexpr u32 upperBound = 1'000'000;
	constexpr u32 numeratorGoal = 3;
	constexpr u32 denominatorGoal = 7;
	std::cout << "Finding closest proper fraction to: " << numeratorGoal << " / " << denominatorGoal << " = " << static_cast<double>(numeratorGoal) / denominatorGoal << std::endl;

	u32 numerator = 0;
	u32 denominator = 1;
	Solve(upperBound, numeratorGoal, denominatorGoal, numerator, denominator);
	std::cout << "Solution 71: " << numerator << "/" << denominator << std::endl;

	return 0;
}
