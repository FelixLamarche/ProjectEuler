// Problem 46: Goldbach's Other Conjecture
// It was proposed that every odd composite number can be written as the sum of a prime and twice of a square
// 9 = 7 + 2 x 1^2
// 15 = 7 + 2 x 2^2
// 21 = 3 + 2 x 3^2
// 25 = 7 + 2 x 3^2
// This is actually false,
// What is the smalles odd composite number that cannot be written as the sum of a prime and twice a square?

#include <iostream>
#include <memory>
#include <vector>

using int64 = long long;

static int64 DoubleSquare(int64 n)
{
	return 2 * (n * n);
}

static int64 Solve()
{
	constexpr int64 sieveCount = 1'000'000;
	using PrimeSieve = std::vector<bool>;

	PrimeSieve primeSieve(sieveCount, true);
	primeSieve[0] = false;
	primeSieve[1] = false;

	for (int64 i = 2; i < sieveCount; ++i)
	{
		for (int64 multiple = 2 * i; multiple < sieveCount; multiple += i)
		{
			primeSieve[multiple] = false;
		}
	}

	for (int64 oddComposite = 9; oddComposite < sieveCount; oddComposite += 2)
	{
		if (primeSieve[oddComposite])
			continue; // Not a composite nb

		int64 doubledSquare = 0;
		bool foundEquation = false;
		for (int64 prime = 2; prime < oddComposite && prime < sieveCount; ++prime)
		{
			if (!primeSieve[prime])
				continue;

			for (int64 doubledSquareN = 1, doubledSquare = DoubleSquare(doubledSquareN);
				doubledSquare < oddComposite;
				++doubledSquareN, doubledSquare = DoubleSquare(doubledSquareN))
			{
				if (prime + doubledSquare == oddComposite)
				{
					foundEquation = true;
					goto outsideLoop;
				}
			}
		}
	outsideLoop:;

		if (!foundEquation)
			return oddComposite;
	}

	return 0;
}

void main()
{
	const int64 solution = Solve();
	std::cout << "Problem 46 Solution: " << solution << std::endl;
}
