#include "Problem2.h"

long long Problem2::Solve(long long limit)
{
	long long a = 2;
	long long b = 1;
	long long sum = 0;

	while (b <= limit)
	{
		if (b % 2 == 0)
		{
			sum += b;
		}
		long long temp = a;
		a = a + b;
		b = temp;
	}

	return sum;
}