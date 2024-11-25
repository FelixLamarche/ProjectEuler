#include "Problem4.h"

#include <numeric>

int Problem4::Solve(int limit)
{
	int largest = 0;
	for (int i = 100; i < 1000; i++)
	{
		for (int j = 100; j <= i; j++)
		{
			int nb = i * j;
			if (nb >= limit)
			{
				break;
			}
			if (IsPalindromic(nb))
			{
				largest = std::max(largest, nb);
			}
		}
	}
	return largest;
}

inline bool Problem4::IsPalindromic(int nb)
{
	return nb > 99999
		&& nb < 1000000
		&& nb / 100000 == nb % 10
		&& (nb % 100000) / 10000 == (nb / 10) % 10
		&& (nb % 10000) / 1000 == (nb / 100) % 10;

}
