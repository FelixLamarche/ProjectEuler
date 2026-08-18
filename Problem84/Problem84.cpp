// Problem 84: Monopoly Odds

#include <algorithm>
#include <array>
#include <cassert>
#include <format>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;

static std::string Solve(const u32 diceSides, const u32 nbDices, const u32 maxTurnCount)
{
	constexpr u32 nbTiles = 40;
	std::array<u32, nbTiles> tileOdds{};

	constexpr u32 goTileIdx = 0;

	constexpr u32 goToJailTileIdx = 30;
	constexpr u32 jailTileIdx = 10;

	constexpr u32 c1TileIdx = 11;
	constexpr u32 e3TileIdx = 24;
	constexpr u32 h2TileIdx = 39;

	constexpr u32 r1TileIdx = 5;
	constexpr u32 r2TileIdx = 15;
	constexpr u32 r3TileIdx = 25;
	constexpr u32 r4TileIdx = 35;

	constexpr u32 u1TileIdx = 12;
	constexpr u32 u2TileIdx = 28;

	constexpr u32 communityChest1Idx = 2;
	constexpr u32 communityChest2Idx = 17;
	constexpr u32 communityChest3Idx = 33;
	constexpr u32 chance1Idx = 7;
	constexpr u32 chance2Idx = 22;
	constexpr u32 chance3Idx = 36;

	constexpr u32 consecutiveDoublesCountForJail = 3;
	constexpr u32 chanceCardCount = 16;
	constexpr u32 communityChestCount = 16;

	std::random_device rd;
	std::mt19937 randomGenerator(rd());
	std::uniform_int_distribution<u32> diceRollDistribution(1, diceSides);


	u32 curDoublesRollCount = 0;
	u32 curTurn = 0;
	u32 curTile = 0;
	u32 curChanceCardIdx = 0;
	u32 curCommunityChestCardIdx = 0;
	for (u32 curTurn = 0; curTurn < maxTurnCount; ++curTurn)
	{
		const u32 dice1Roll = diceRollDistribution(randomGenerator);
		const u32 dice2Roll = diceRollDistribution(randomGenerator);
		const u32 diceRoll = dice1Roll + dice2Roll;

		if (dice1Roll == dice2Roll)
		{
			++curDoublesRollCount;
		}
		else
		{
			curDoublesRollCount = 0;
		}

		bool goToJail = curDoublesRollCount == consecutiveDoublesCountForJail;

		u32 nextTile = (curTile + diceRoll) % nbTiles;

		if (goToJail)
		{
			nextTile = jailTileIdx;
		}
		else
		{
			switch (nextTile)
			{
			case goToJailTileIdx:
				nextTile = jailTileIdx;
				goToJail = true;
				break;
			case communityChest1Idx:
			case communityChest2Idx:
			case communityChest3Idx:
			{
				if (curCommunityChestCardIdx == 0)
				{
					nextTile = goTileIdx;
				}
				else if (curCommunityChestCardIdx == 1)
				{
					nextTile = jailTileIdx;
					goToJail = true;
				}
				curCommunityChestCardIdx = (curCommunityChestCardIdx + 1) % communityChestCount;
			}
			break;
			case chance1Idx:
			case chance2Idx:
			case chance3Idx:
			{
				if (curChanceCardIdx == 0)
				{
					nextTile = goTileIdx;
				}
				else if (curChanceCardIdx == 1)
				{
					nextTile = jailTileIdx;
					goToJail = true;
				}
				else if (curChanceCardIdx == 2)
				{
					nextTile = c1TileIdx;
				}
				else if (curChanceCardIdx == 3)
				{
					nextTile = e3TileIdx;
				}
				else if (curChanceCardIdx == 4)
				{
					nextTile = h2TileIdx;
				}
				else if (curChanceCardIdx == 5)
				{
					nextTile = r1TileIdx;
				}
				else if (curChanceCardIdx == 6 || curChanceCardIdx == 7) // go to next R
				{
					if (nextTile >= r4TileIdx || nextTile < r1TileIdx)
						nextTile = r1TileIdx;
					else if (nextTile >= r3TileIdx)
						nextTile = r4TileIdx;
					else if (nextTile >= r2TileIdx)
						nextTile = r3TileIdx;
					else
						nextTile = r2TileIdx;
				}
				else if (curChanceCardIdx == 8) // Go to next U
				{
					if (nextTile >= u2TileIdx || nextTile < u1TileIdx)
						nextTile = u1TileIdx;
					else
						nextTile = u2TileIdx;
				}
				else if (curChanceCardIdx == 9) 
				{
					assert(nextTile >= 3);
					nextTile = nextTile - 3;
				}
				curChanceCardIdx = (curChanceCardIdx + 1) % chanceCardCount;
			}
			break;
			}
		}

		if (goToJail)
		{
			curDoublesRollCount = 0;
		}

		++tileOdds[nextTile];
		curTile = nextTile;
	}

	const double rollCount = std::accumulate(tileOdds.begin(), tileOdds.end(), 0);

	u32 tileBest1 = 0;
	double tileBest1Percentage = 0.0;
	u32 tileBest2 = 0;
	double tileBest2Percentage = 0.0;
	u32 tileBest3 = 0;
	double tileBest3Percentage = 0.0;
	for (u32 i = 0; i < tileOdds.size(); ++i)
	{
		const double percentage = 100.0 * tileOdds[i] / rollCount;

		if (percentage > tileBest1Percentage)
		{
			tileBest3Percentage = tileBest2Percentage;
			tileBest3 = tileBest2;
			tileBest2Percentage = tileBest1Percentage;
			tileBest2 = tileBest1;

			tileBest1 = i;
			tileBest1Percentage = percentage;
		}
		else if (percentage > tileBest2Percentage)
		{
			tileBest3Percentage = tileBest2Percentage;
			tileBest3 = tileBest2;

			tileBest2Percentage = percentage;
			tileBest2 = i;
		}
		else if (percentage > tileBest3Percentage)
		{
			tileBest3Percentage = percentage;
			tileBest3 = i;
		}
		LOGFMT("[i: {}]: {} %\n", i, percentage);
	}

	std::string bestTilesStr = std::format("{:02}", tileBest1) + std::format("{:02}", tileBest2) + std::format("{:02}", tileBest3);
	return bestTilesStr;
}

int main()
{
	constexpr u32 diceSides = 4;
	constexpr u32 diceCount = 2;
	constexpr u32 turnCount = 100'000'000;
	const std::string sol = Solve(diceSides, diceCount, turnCount);
	std::cout << "Solution 84: " << sol << std::endl;

	return 0;
}