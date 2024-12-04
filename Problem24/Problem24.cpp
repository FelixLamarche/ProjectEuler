// Problem 24: Lexicographic permutations
// Given a number N, return the Nth lexicographic permutation of the string 'abcdefghijklm'.

#include <iostream>
#include <string>

static long long Factorial(long long N)
{
	if (N == 0)
	{
		return 1;
	}
	return N * Factorial(N - 1);
}

static std::string Solve(long long N)
{
	const std::string str = "abcdefghijklm";
	std::string chars = str;
	std::string ans;

	for (size_t i = 0; i < str.size(); i++)
	{
		const size_t idx = ((N - 1) / Factorial(str.size() - i - 1)) % chars.size();
		ans += chars[idx];
		chars.erase(chars.begin() + idx);
	}
	return ans;
}

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; ++i)
	{
		long long N;
		std::cin >> N;
		std::cout << Solve(N) << std::endl;
	}

	return 0;
}