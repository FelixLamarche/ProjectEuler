// Problem 20: Factorial digit sum

#include <iostream>
#include <vector>

static int Solve(int N)
{
	constexpr unsigned long long max_nb = 1'000'000;
	// Each number is stored in a vector of nbs from [0-999999]
	std::vector<unsigned long long> nbs{ 1 };

	for (int i = 2; i <= N; i++)
	{
		unsigned long long ret = 0;
		for (size_t j = 0; j < nbs.size(); j++)
		{
			unsigned long long n = nbs[j] * i + ret;
			ret = n / max_nb;
			n %= max_nb;
			nbs[j] = n;
		}
		if (ret)
		{
			nbs.push_back(ret);
		}
	}

	int sum = 0;
	for (size_t i = 0; i < nbs.size(); i++)
	{
		unsigned long long nb = nbs[i];
		while (nb)
		{
			sum += nb % 10;
			nb /= 10;
		}
	}

	return sum;
}

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++)
	{
		int N;
		std::cin >> N;
		std::cout << Solve(N) << std::endl;
	}

	return 0;
}