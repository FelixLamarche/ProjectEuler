// Problem 31: Coin Sums
// How many different ways to make up 2 Pounds with any number of conis coins from (1p, 2p, 5p, 10p, 20p, 100p, 200p)

#include <iostream>
#include <format>
#include <array>
#include <vector>

#define LOG(str) std::cout << str << std::endl
#define LOGF(str, ...) printf(str, __VA_ARGS__)

static constexpr int defaultValue = -1;
static constexpr int nbCoins = 8;
static constexpr int coins[nbCoins] = { 1, 2, 5, 10, 20, 50, 100, 200 };

using SolutionMap = std::vector<std::array<int, nbCoins>>;
static int SolveImpl(SolutionMap& waysToCreateTarget, const int target, const int maxCoinIndex)
{
	if (target < 0) return 0;
	if (waysToCreateTarget[target][maxCoinIndex] != defaultValue)
		return waysToCreateTarget[target][maxCoinIndex];

	int targetSolution = 0;
	for(int coinIdx = maxCoinIndex; coinIdx >= 0; --coinIdx)
	{
		const int coin = coins[coinIdx];
		const int solutionCount = SolveImpl(waysToCreateTarget, target - coin, coinIdx);
		if (solutionCount <= 0) continue;
		targetSolution += solutionCount;
		//LOGF("target:%i maxCoin:%i: +%i from: %i\n", target, coins[maxCoinIndex], delta, target - coin);
	}
	waysToCreateTarget[target][maxCoinIndex] = targetSolution;
	//LOGF("%i maxCoin:%i : %i possibilities.\n", target, coins[maxCoinIndex], targetSolution);
	return targetSolution;
}

static void Solve(const int target)
{
	std::array<int, nbCoins> waysToSumToTargetPerCoinIndex;
	waysToSumToTargetPerCoinIndex.fill(defaultValue);
	SolutionMap solutionMap(target + 1, waysToSumToTargetPerCoinIndex);
	solutionMap[0].fill(1);
	solutionMap[1].fill(1);

	constexpr int maxCoinIndex = nbCoins - 1;
	SolveImpl(solutionMap, target, maxCoinIndex);
	const int solution = solutionMap[target][nbCoins - 1];
	std::cout << "Problem 31 Solution: target:" << target << ": possibilities: " << solution << std::endl;
}

void main()
{
	const int target = 200;
	Solve(target);
}