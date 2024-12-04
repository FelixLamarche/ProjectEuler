// Problem 25: N-digit Fibonacci number
// What is the first fibonacci number which has N digits.
// 2 <= N <= 5000

#include <iostream>
#include <vector>

static std::string AddBigStrings(const std::string& a, const std::string& b)
{
	std::string sum;
	sum.reserve(a.size() + 1);
	int carry = 0;
	for (size_t i = 0; i < a.size() || i < b.size() || carry; i++)
	{
		if (i < a.size())
		{
			carry += a[a.size() - i - 1] - '0';
		}
		if (i < b.size())
		{
			carry += b[b.size() - i - 1] - '0';
		}
		sum.insert(sum.begin(), carry % 10 + '0');
		carry /= 10;
	}
	return sum;
}

static size_t Solve(int N)
{
	static std::vector<std::string> fibonacci{ "0", "1", "1"};
	static std::vector<size_t> firstToNDigits{ 1 };

	// Populate cache of first N digits
	if (firstToNDigits.size() <= N)
	{
		fibonacci.reserve(N + 1);
		firstToNDigits.reserve(N + 1);

		while (firstToNDigits.size() < N + 1)
		{
			const std::string sum = AddBigStrings(*(fibonacci.end() - 1), *(fibonacci.end() - 2));
			fibonacci.push_back(sum);

			if (sum.size() >= firstToNDigits.size())
			{
				firstToNDigits.push_back(fibonacci.size() - 1);
			}
		}
	}

	return firstToNDigits[N];
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