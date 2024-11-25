#include "Problem1.h"

Problem1::BigNumber Problem1::Solve(int limit)
{
	// 3 + 6 + 9 + 12 + ... = 3 + 3*2 + 3*3 + 3*4 + ...
	// = 3 * (n + 1)*n/2
	const long long nb_3 = (limit - 1) / 3;
	const long long nb_5 = (limit - 1) / 5;
	const long long nb_15 = (limit - 1) / 15;

	long long sum = 0;

	if (nb_3 > 0)
	{
		sum += static_cast<long long>(3) * nb_3 * (nb_3 + 1) / 2;
	}
	if (nb_5 > 0)
	{
		sum += static_cast<long long>(5) * nb_5 * (nb_5 + 1) / 2;
	}
	if (nb_15 > 0)
	{
		sum -= static_cast<long long>(15) * nb_15 * (nb_15 + 1) / 2;
	}

	return sum;
}

long long Problem1::SolveInefficient(int limit)
{
	long long sum = 0;
	for (int i = 0; i < limit; i++)
	{
		if (i % 3 == 0 || i % 5 == 0)
		{
			sum += i;
		}
	}
	return sum;
}