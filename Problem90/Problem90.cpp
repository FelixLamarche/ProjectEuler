// Problem 90: Cube Digit Pairs

#include <array>
#include <format>
#include <iostream>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

struct NumberPair
{
	u32 first;
	u32 second;
};
using NumberPairs = std::array<NumberPair, 8>;
using Dice = std::array<u32, 6>;

static bool CanDicesFormPair(const Dice& dice1, const Dice& dice2, const u32 nb1, const u32 nb2)
{
	return (std::find(dice1.begin(), dice1.end(), nb1) != dice1.end() && std::find(dice2.begin(), dice2.end(), nb2) != dice2.end())
		|| (std::find(dice1.begin(), dice1.end(), nb2) != dice1.end() && std::find(dice2.begin(), dice2.end(), nb1) != dice2.end());

}

static bool CanDicesFormPairs(const Dice& dice1, const Dice& dice2)
{
	if (!CanDicesFormPair(dice1, dice2, 0, 1))
		return false;
	if (!CanDicesFormPair(dice1, dice2, 0, 4))
		return false;
	if (!(CanDicesFormPair(dice1, dice2, 0, 6) || CanDicesFormPair(dice1, dice2, 0, 9)))
		return false;
	if (!(CanDicesFormPair(dice1, dice2, 1, 6) || CanDicesFormPair(dice1, dice2, 1, 9)))
		return false;
	if (!CanDicesFormPair(dice1, dice2, 2, 5))
		return false;
	if (!(CanDicesFormPair(dice1, dice2, 3, 6) || CanDicesFormPair(dice1, dice2, 3, 9)))
		return false;
	if (!(CanDicesFormPair(dice1, dice2, 4, 6) || CanDicesFormPair(dice1, dice2, 4, 9)))
		return false;
	if (!CanDicesFormPair(dice1, dice2, 1, 8))
		return false;
	return true;
}

static bool CanDicesFormPairs(const NumberPairs& numberPairs, const Dice& dice1, const Dice& dice2)
{
	for (const NumberPair& numberPair : numberPairs)
	{
		if (!CanDicesFormPair(dice1, dice2, numberPair.first, numberPair.second))
			return false;
	}
	return true;
}

static u64 SolveIter(const NumberPairs& numberPairs, Dice& dice1, const u32 dice1Idx, Dice& dice2, const u32 dice2Idx)
{
	if (dice2Idx == dice2.size())
	{
		const bool isValidSolution = CanDicesFormPairs(dice1, dice2);
		if (isValidSolution)
		{
			LOGFMT("Dice1: {}, {}, {}, {}, {}, {}\n", dice1[0], dice1[1], dice1[2], dice1[3], dice1[4], dice1[5]);
			LOGFMT("Dice2: {}, {}, {}, {}, {}, {}\n\n", dice2[0], dice2[1], dice2[2], dice2[3], dice2[4], dice2[5]);
			return 1;
		}
		else
		{
			return 0;
		}
	}

	const bool isIteratingDice1 = dice1Idx < dice1.size();
	Dice& diceToIterate = isIteratingDice1 ? dice1 : dice2;
	const u32 diceIdx = isIteratingDice1 ? dice1Idx : dice2Idx;
	u32 startingDigit = 0;
	startingDigit = diceIdx == 0 ? 0 : diceToIterate[diceIdx - 1] + 1;

	constexpr u32 maxDigit = 9;
	u64 solutionCount = 0;
	for (u32 digit = startingDigit; digit <= maxDigit; ++digit)
	{
		diceToIterate[diceIdx] = digit;
		if (isIteratingDice1)
			solutionCount += SolveIter(numberPairs, dice1, dice1Idx + 1, dice2, dice2Idx);
		else
			solutionCount += SolveIter(numberPairs, dice1, dice1Idx, dice2, dice2Idx + 1);
	}
	return solutionCount;
}

static u64 Solve()
{

	// Squares to form: 01, 04, 09, 16, 25, 36, 49, 64, 81
	// Consider 9s to be 6s: 01, 04, 06, 16, 25, 36, 46, 64, 81
	const NumberPairs numberPairs{ NumberPair{0, 1}, {0, 4}, {0, 6}, {1, 6}, {2, 5}, {3, 6}, {4, 6}, {1, 8} };

	Dice dice1{ 0, 0, 0, 0, 0, 0 };
	u32 diceIdx1 = 0;
	Dice dice2{ 0, 0, 0, 0, 0, 0 };
	u32 diceIdx2 = 0;

	// We are counting the dices twice by iterating through all ordering for both
	const u32 doubledSol = SolveIter(numberPairs, dice1, diceIdx1, dice2, diceIdx2);
	return doubledSol / 2;
}

int main()
{
	const u64 sol = Solve();
	std::cout << "Solution 90: " << sol << std::endl;

	return 0;
}
