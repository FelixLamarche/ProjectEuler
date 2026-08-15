// Problem 78: Coin Partitions

#include <format>
#include <iostream>
#include <vector>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;

static u64 Solve(const int summationDivider)
{
	// See Partition Function to see how partition counts are calculated
	std::vector<int> countsModulo;
	countsModulo.push_back(1); // [0] = 1, by definition
	int nb = 0;
	while (true)
	{
		++nb;
		int sum = 0;
		int k = 1;

		//LOGFMT("Nb:{}\n", nb);

		while (true)
		{
			int sign = k % 2 == 0 ? -1 : 1;

			int idx = nb - k * (3 * k - 1) / 2;
			if (idx < 0)
				break;
			int additional = (sign * countsModulo[idx]) % summationDivider;
			sum = (sum + additional) % summationDivider;
			//LOGFMT("Sum:{}\n", sum);

			k *= -1;
			idx = nb - k * (3 * k - 1) / 2;
			if (idx < 0)
				break;
			additional = (sign * countsModulo[idx]) % summationDivider;
			sum = (sum + additional) % summationDivider;
			//LOGFMT("Sum:{}\n", sum);

			k *= -1;
			++k;
		}
		//LOGFMT("Nb:{} = Sum:{}\n", nb, sum);
		//LOGFMT("\n");

		countsModulo.push_back(sum);
		if (sum % summationDivider == 0)
			break;
	}

	return nb;
}

int main()
{
	const int upperBound = 1'000'000;
	const u64 sol = Solve(upperBound);
	std::cout << "Solution 78: " << sol << std::endl;

	return 0;
}