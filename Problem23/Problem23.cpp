/// Problem 23 - Non-abundant Sums
/// An abundant sum is a number that is less than the sum of its proper divisors.
/// With proper divisors being all positive divisors of the number excluding the number itself.
/// Given a number N return whether or not the number can be written as the sum of two abundant numbers.

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


static bool CanBeSumOfTwoAbundantNumbers(int N)
{
	static std::vector<int> properDividerSums;
	static std::vector<int> abundantNumbers;
	typedef typename std::vector<int>::const_iterator ConstIt;

	// Populate dividersums and relevant abundant numbers
	if (properDividerSums.size() < N + 1)
	{
		properDividerSums.reserve(N + 1);
		for (int i = static_cast<int>(properDividerSums.size()); i < N + 1; ++i)
		{
			const int dividerSum = GetProperDividerSum(i);
			properDividerSums.push_back(dividerSum);
			if (dividerSum > i)
			{
				abundantNumbers.push_back(i);
			}
		}
	}

	// Check if N can be written as the sum of two abundant numbers
	ConstIt smallIdx = abundantNumbers.begin();
	// Find a good approximation for the upper bound
	ConstIt largeIdx = std::lower_bound(abundantNumbers.begin(), abundantNumbers.end(), N);
	if (largeIdx == abundantNumbers.end())
	{
		--largeIdx;
	}
	while (smallIdx <= largeIdx)
	{
		const int sum = *smallIdx + *largeIdx;
		if (sum == N)
		{
			return true;
		}
		else if (sum < N)
		{
			++smallIdx;
		}
		else
		{
			--largeIdx;
		}
	}

	return false;
}

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; ++i)
	{
		int N;
		std::cin >> N;

		if (CanBeSumOfTwoAbundantNumbers(N))
		{
			std::cout << "YES" << std::endl;
		}
		else
		{
			std::cout << "NO" << std::endl;
		}
	}
	return 0;
}