// Problem 53 Combinatoric Selections
// How many values of n choose r are greater than 1 million for  1 <= n <= 100

#include <iostream>
#include <vector>

#define LOGF(str, ...) do {printf(str, __VA_ARGS__);} while(0)

static bool IsNChooseRAboveValue(int n, int r, double targetValue)
{
	double product = 1;
	int nMinusR = n - r;

	for (int i = n; i > r; --i)
	{
		product *= i;
	}

	for (int i = 1; i <= nMinusR; ++i)
	{
		product /= i;
	}

	return product > targetValue;
}

static int Solve()
{
	constexpr double targetValueMin = 1'000'000;
	constexpr double nMax = 100;

	int count = 0;

	for (double n = 1; n <= nMax; ++n)
	{
		for (double r = 1; r <= n; ++r)
		{
			if (IsNChooseRAboveValue(n, r, targetValueMin))
			{
				++count;
			}
		}
	}

	return count;
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 53 Solution: " << solution << std::endl;
}
