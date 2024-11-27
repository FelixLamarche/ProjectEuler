#include "Problem14.h"

#include <map>
#include <numeric>
#include <vector>


long long Problem14::Solve(long long N)
{
	constexpr int MAX = 5000001;
	static std::vector<int> counts(MAX, 0);
	static std::map<long long, int> biggests{ {1,1} };
	static long long largestN = 1;

	counts[1] = 1;
	long long biggest;
	int biggestCount;
	auto it = biggests.lower_bound(N);
	if (it != biggests.end() && it->first == N)
	{
		return it->first;
	}
	--it;
	biggest = it->first;
	biggestCount = it->second;

	for (long long i = largestN; i <= N; i++)
	{
		largestN = std::max(largestN, i);
		if (counts[i] != 0)
		{
			continue;
		}
		// else compute
		int count = 0;
		long long nb = i;
		std::vector<long long> nbsToCompute;
		// nb will be in counts as it will eventually be 1, which is in cache
		while (nb >= static_cast<long long>(counts.size()) || counts[nb] == 0)
		{
			nbsToCompute.push_back(nb);

			// Collatz conjecture
			if (nb % 2 == 0)
			{
				nb /= 2;
			}
			else
			{
				nb = 3 * nb + 1;
			}
			count++;
		}
		count += counts[nb];

		// Insert all known values in cache
		for (size_t i = 0; i < nbsToCompute.size(); i++)
		{
			if (nbsToCompute[i] < static_cast<long long>(counts.size()))
			{
				counts[nbsToCompute[i]] = count - static_cast<int>(i);
			}
		}

		if (count >= biggestCount)
		{
			biggestCount = count;
			biggest = i;
			biggests[i] = biggestCount;
		}
	}

	return biggest;
}