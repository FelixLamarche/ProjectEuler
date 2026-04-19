// Problem 33: Digit Cancelling Fractions

#include <iostream>
#include <functional>

static bool AreFractionsEqual(const int numeratorA, const int denominatorA, const int numeratorB, const int denominatorB)
{
	return numeratorA * denominatorB / denominatorA == numeratorB && (numeratorA * denominatorB) % denominatorA == 0;
}

static void Solve()
{
	constexpr int maxDenominator = 99;
	int numeratorProduct = 1;
	int denominatorProduct = 1;

	for (int denominator = 11; denominator <= maxDenominator; ++denominator)
	{
		if (denominator % 10 == 0) continue;
		
		for (int numerator = 11; numerator < denominator; ++numerator)
		{
			if (numerator % 10 == 0) continue;
			const int numerators[] = { numerator % 10, numerator / 10 };
			const int denominators[] = { denominator % 10, denominator / 10 };

			for (int numIdx = 0; numIdx < 2; ++numIdx)
			{
				for (int denomIdx = 0; denomIdx < 2; ++denomIdx)
				{
					const int num = numerators[numIdx];
					const int denom = denominators[denomIdx];

					if (numerators[(numIdx + 1) % 2] == denominators[(denomIdx + 1) % 2]
						&& AreFractionsEqual(numerator, denominator, num, denom))
					{
						std::cout << numerator << "/" << denominator << " = " << num << "/" << denom << std::endl;
						numeratorProduct *= num;
						denominatorProduct *= denom;
					}
				}
			}
		}
	}
	
	const int solutionNumerator = numeratorProduct / numeratorProduct;
	const int solutionDenominator = denominatorProduct / numeratorProduct;

	std::cout << "\nProblem 33 Solution: " << solutionNumerator << "/" << solutionDenominator << std::endl;
}

void main()
{
	Solve();
}