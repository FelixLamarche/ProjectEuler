// Problem 52: Permuted Multiples
// It is seen that 125874 and its double 251748, contain exactly the same digits
// Find the smallest integer x such that 2x, 3x, 4x, 5x and 6x contain the same digits

#include <iostream>

using uint = unsigned int;

static uint GetDigitsFlag(int nb)
{
	uint digitsFlag = 0;

	while (nb > 0)
	{
		int digit = nb % 10;
		uint digitFlag = 1 << digit;
		digitsFlag |= digitFlag;

		nb /= 10;
	}

	return digitsFlag;
}

static int Solve()
{
	constexpr int multiplesGoal = 6;

	constexpr int upperBound = 1'000'000;
	for (int n = 1; n < upperBound; ++n)
	{
		const uint digitsFlag = GetDigitsFlag(n);

		int multiple;
		for (multiple = 2; multiple <= multiplesGoal; ++multiple)
		{
			if (digitsFlag != GetDigitsFlag(multiple * n))
				break;
		}
		if (multiple == multiplesGoal + 1)
			return n;
	}
	return 0;
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 52 Solution: " << solution << std::endl;
}
