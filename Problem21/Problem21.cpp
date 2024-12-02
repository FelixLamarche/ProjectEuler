// Problem21 : Amicable numbers
// The proper divisors of a number N are the integers less than N dividing evenly into it
// Amicable numbers are two numbers a, b, a != b, where d(a) = b and d(b) = a
// Where d(n) = Sum of the proper divisors of n
//
// Evaluate the sum of all amicable numbers below N

#include <cmath>
#include <iostream>
#include <vector>

static int GetProperDividerSum(int N)
{
	static std::vector<int> cache(N + 1, 0);

	if (cache.size() > N && cache[N] != 0)
	{
		return cache[N];
	}

	int sum = 1;
	const int sqrtN = static_cast<int>(std::sqrt(N));
	for (int i = 2; i <= sqrtN; ++i)
	{
		if (N % i == 0)
		{
			sum += i + N / i;
		}
	}
	if (N == sqrtN * sqrtN)
	{
		// Was counted twice in the loop
		sum -= sqrtN;
	}

	if (cache.size() <= N)
	{
		cache.resize(N + 1, 0);
	}
	cache[N] = sum;
	return sum;
}

static int Solve(int N)
{
	std::vector<int> properDividerSums(N, 0);
	for (int i = 1; i < N; i++)
	{
		properDividerSums[i] = GetProperDividerSum(i);
	}

	int sum = 0;
	for (int i = 1; i < N; i++)
	{
		const int dividerSum = properDividerSums[i];
		const int dividerSumDividerSum = dividerSum >= N ? GetProperDividerSum(dividerSum) : properDividerSums[dividerSum];
		bool isAmicable = dividerSumDividerSum == i && dividerSum != i;
		if (isAmicable)
		{
			sum += i;
		}
	}
	return sum;
}

int main()
{
	int T;
	std::cin >> T;

	int ans_before = 0;
	for (int i = 0; i < T; i++)
	{
		int N;
		std::cin >> N;
		std::cout << Solve(N) << std::endl;
	}
	return 0;
}