// Problem 34 Digit Factorials
// Find the sum of all numbers which equal the sum of their factorial digits (e.g. 145 = 1! + 4! + 5!)

#include <iostream>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__);} while(false)

static int Factorial(int num)
{
	if (num < 0) return 0;
	int factorial = 1;
	while (num > 0)
	{
		factorial *= num;
		--num;
	}
	return factorial;
}

static int SumOfFactorialDigits(int num)
{
	int sum = 0;
	while (num > 0)
	{
		sum += Factorial(num % 10);
		num /= 10;
	}
	return sum;
}

static int Solve()
{
	constexpr int maxLimit = 1'000'000; // Could not properly prove an upper bound, use a large number instead

	int solutionSum = 0;
	for (int i = 3; i < maxLimit; ++i)
	{
		if (SumOfFactorialDigits(i) == i)
		{
			LOGF("%i is a factorial digit sum.\n", i);
			solutionSum += i;
		}
	}

	return solutionSum;
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 34 Solution: " << solution << std::endl;
}
