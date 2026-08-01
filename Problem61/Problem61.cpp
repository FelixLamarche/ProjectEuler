// Problem 61: Cyclical Figurate Numbers

#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <numeric>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;
using figurateFuncPtr = u64(*)(u64);

static u64 TriangleNumber(u64 n)
{
	return n * (n + 1) / 2;
}

static u64 SquareNumber(u64 n)
{
	return n * n;
}

static u64 PentagonalNumber(u64 n)
{
	return n * (3 * n - 1) / 2;
}

static u64 HexagonalNumber(u64 n)
{
	return n * (2 * n - 1);
}

static u64 HeptagonalNumber(u64 n)
{
	return n * (5 * n - 3) / 2;
}

static u64 OctagonalNumber(u64 n)
{
	return n * (3 * n - 2);
}

static bool SolveIteration(
	std::vector<u64>& cycleFigurateNbs,
	const u64 cycleFigurateIdx,
	const u64 nbOfFiguratesType,
	std::vector<u64>* const* const nbLists,
	const std::vector<u64>& figurateIdxsLeft)
{
	if (figurateIdxsLeft.empty())
		return true;

	for (u64 figurateIdxLeft : figurateIdxsLeft)
	{
		const std::vector<u64>& figurateNbs = *nbLists[figurateIdxLeft];

		std::vector<u64> newFigurateIdxsLeft = figurateIdxsLeft;
		std::erase(newFigurateIdxsLeft, figurateIdxLeft);

		for (const u64 figurateNb : figurateNbs)
		{
			if (cycleFigurateIdx > 0)
			{
				const u64 figurateDigitsStart = cycleFigurateNbs[cycleFigurateIdx - 1] % 100;
				if (figurateNb / 100 != figurateDigitsStart)
					continue;
			}

			if (cycleFigurateIdx == nbOfFiguratesType - 1)
			{
				const u64 figurateDigitsEnd = cycleFigurateNbs[0] / 100;
				if (figurateNb % 100 != figurateDigitsEnd)
					continue;

				cycleFigurateNbs[cycleFigurateIdx] = figurateNb;
				return true;
			}

			cycleFigurateNbs[cycleFigurateIdx] = figurateNb;
			const bool isSolved = SolveIteration(cycleFigurateNbs, cycleFigurateIdx + 1, nbOfFiguratesType, nbLists, newFigurateIdxsLeft);

			if (isSolved)
				return true;
		}
	}

	return false;
}

static u64 Solve()
{
	constexpr int nbFigurateTypes = 6;

	std::vector<u64> triangleNbs;
	std::vector<u64> squareNbs;
	std::vector<u64> pentagonalNbs;
	std::vector<u64> hexagonalNbs;
	std::vector<u64> heptagonalNbs;
	std::vector<u64> octagonalNbs;

	std::array<std::vector<u64>*, nbFigurateTypes> figurateNbLists{ &triangleNbs, &squareNbs, &pentagonalNbs, &hexagonalNbs, &heptagonalNbs, &octagonalNbs };

	figurateFuncPtr figurateFuncs[] = { TriangleNumber, SquareNumber, PentagonalNumber, HexagonalNumber, HeptagonalNumber, OctagonalNumber };

	// Get all 4-digit numbers of their figurate type
	for (u32 figurateType = 0; figurateType < figurateNbLists.size(); ++figurateType)
	{
		u64 i = 0;
		while (true)
		{
			++i;
			const u64 figurateNb = figurateFuncs[figurateType](i);
			if (figurateNb >= 10000)
				break;
			if (figurateNb < 1000)
				continue;

			figurateNbLists[figurateType]->push_back(figurateNb);
		}
	}

	std::vector<u64> cycleOfFigurates(nbFigurateTypes, 0);
	std::vector<u64> figuratesIdxs(nbFigurateTypes, 0);
	std::iota(figuratesIdxs.begin(), figuratesIdxs.end(), 0);

	SolveIteration(cycleOfFigurates, 0, nbFigurateTypes, figurateNbLists.data(), figuratesIdxs);

	std::cout << "Numbers:\n";
	for (u64 nb : cycleOfFigurates)
	{
		std::cout << nb << "\n";
	}
	std::cout << std::endl;

	const u64 cycleSum = std::accumulate(cycleOfFigurates.begin(), cycleOfFigurates.end(), 0);
	return cycleSum;
}

void main() {
	const u64 sol = Solve();
	std::cout << "Solution 61: " << sol << std::endl;
}
