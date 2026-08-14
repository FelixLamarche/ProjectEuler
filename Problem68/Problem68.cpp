// Problem 68 : Magic 5-Gon Ring

#include <array>
#include <format>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

static u64 SolveIteration(std::vector<u32>& nbsUsed, const std::vector<u32>& nbsLeft)
{
	constexpr u32 nbNodeOutside = 5;
	// Return an answer
	if (nbsLeft.empty())
	{
		const u32 sum0 = nbsUsed[5] + nbsUsed[0] + nbsUsed[1];
		const u32 sum1 = nbsUsed[6] + nbsUsed[1] + nbsUsed[2];
		const u32 sum2 = nbsUsed[7] + nbsUsed[2] + nbsUsed[3];
		const u32 sum3 = nbsUsed[8] + nbsUsed[3] + nbsUsed[4];
		const u32 sum4 = nbsUsed[9] + nbsUsed[4] + nbsUsed[0];

		if (sum0 != sum1 || sum0 != sum2 || sum0 != sum3 || sum0 != sum4)
			return 0;

		// have to start with min number
		u32 minOutsideNbIdx = nbNodeOutside;
		for (u32 i = minOutsideNbIdx; i < nbsUsed.size(); ++i)
		{
			if (nbsUsed[i] < nbsUsed[minOutsideNbIdx])
				minOutsideNbIdx = i;
		}

		// do concatanation
		u64 sol = 0;
		for (u32 i = 0; i < nbNodeOutside; ++i)
		{
			const u32 nbIdxStart = ((minOutsideNbIdx + i) % nbNodeOutside) + nbNodeOutside;

			sol *= 10;
			if (nbsUsed[nbIdxStart] >= 10)
				sol *= 10;
			sol += nbsUsed[nbIdxStart];

			sol *= 10;
			const u32 nbIdx2 = nbIdxStart % 5;
			if (nbsUsed[nbIdx2] >= 10)
				sol *= 10;
			sol += nbsUsed[nbIdx2];

			sol *= 10;
			const u32 nbIdx3 = (nbIdxStart + 1) % 5;
			if (nbsUsed[nbIdx3] >= 10)
				sol *= 10;
			sol += nbsUsed[nbIdx3];
		}

		u64 biggestAllowedNb = 10'000'000'000'000'000;
		if (sol < biggestAllowedNb)
			return sol;
		return 0;
	}

	u64 biggestSol = 0;
	for (const u32 nbLeft : nbsLeft)
	{
		nbsUsed.push_back(nbLeft);
		std::vector<u32> newNbsLeft;
		newNbsLeft.reserve(nbsLeft.size() - 1);
		for (const u32 nb : nbsLeft)
		{
			if (nb != nbLeft)
				newNbsLeft.push_back(nb);
		}
		const u64 iterationSol = SolveIteration(nbsUsed, newNbsLeft);
		biggestSol = std::max(biggestSol, iterationSol);
		nbsUsed.pop_back();
	}

	return biggestSol;
}

static u64 Solve()
{
	const std::vector<u32> nbs{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	std::vector<u32> nbsUsed;
	nbsUsed.reserve(10);

	return SolveIteration(nbsUsed, nbs);
}


void main()
{
	const u64 sol = Solve();
	std::cout << "Solution 68: " << sol << std::endl;
}