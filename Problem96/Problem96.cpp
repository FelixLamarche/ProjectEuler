// Problem 96 : Su Doku

#include <array>
#include <cassert>
#include <format>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

struct Coord
{
	u32 x;
	u32 y;
};

struct Sudoku
{
	static const u32 boardSize = 9;
	static const u32 unsetDigit = 0;
	// board[y][x]
	std::array<std::array<u32, boardSize>, boardSize> board;

	u32 GetDigit(const int x, const int y) const { return board[y][x]; }
	u32 GetDigit(const Coord coord) const { return board[coord.y][coord.x]; }
	void SetDigit(const int x, const int y, const u32 digit) { board[y][x] = digit; }
	void SetDigit(const Coord coord, const u32 digit) { board[coord.y][coord.x] = digit; }
};

struct DigitPossibility
{
	enum Number {
		None = 0,
		One = 1 << 0,
		Two = 1 << 1,
		Three = 1 << 2,
		Four = 1 << 3,
		Five = 1 << 4,
		Six = 1 << 5,
		Seven = 1 << 6,
		Eight = 1 << 7,
		Nine = 1 << 8
	};

	Number possibility = Number::None;

	bool IsEmpty() const
	{
		return possibility == Number::None;
	}
	void SetToAllDigits()
	{
		possibility = static_cast<Number>(0b111111111);
	}
	void Clear()
	{
		possibility = Number::None;
	}
	bool HasDigit(const u32 digit) const
	{
		return possibility & (1 << (digit - 1));
	}
	void RemoveDigit(const u32 digit)
	{
		if (HasDigit(digit))
			possibility = static_cast<Number>(possibility & ~(1 << (digit - 1)));
	}
	u32 PossibilityCount() const
	{
		u32 count = 0;
		for (u32 nb = 1; nb <= 9; ++nb)
		{
			if (HasDigit(nb))
				++count;
		}
		return count;
	}

	std::vector<u32> GetNumbers() const
	{
		std::vector<u32> nbs;
		for (u32 nb = 1; nb <= 9; ++nb)
		{
			if (HasDigit(nb))
				nbs.push_back(nb);
		}
		return nbs;
	}
};

struct CoordQueued {
	Coord coord;
	DigitPossibility digitPossibilities;
};

struct CoordComperator {
	bool operator() (const CoordQueued& coord1, const CoordQueued& coord2) const {
		return coord1.digitPossibilities.PossibilityCount() > coord2.digitPossibilities.PossibilityCount();
	}
};

using CoordPriorityQueue = std::priority_queue<CoordQueued, std::vector<CoordQueued>, CoordComperator>;


struct SudokuSolution
{
	Sudoku board;
	std::array<std::array<DigitPossibility, Sudoku::boardSize>, Sudoku::boardSize> boardTilePossibilities;
	CoordPriorityQueue coordQueue;
};

static std::vector<Sudoku> ReadFile(const char* filePath)
{
	std::ifstream fileStream(filePath);
	if (!fileStream.is_open())
	{
		std::cout << "Could not open file: " << filePath << std::endl;
		return {};
	}

	std::vector<Sudoku> sudokuBoards;
	std::string readStr;
	while (std::getline(fileStream, readStr))
	{
		// reading a grid
		Sudoku& newBoard = sudokuBoards.emplace_back();
		for (u32 y = 0; y < Sudoku::boardSize; ++y)
		{
			std::getline(fileStream, readStr);
			for (u32 x = 0; x < Sudoku::boardSize; ++x)
			{
				const u32 digit = readStr[x] - '0';
				newBoard.SetDigit(x, y, digit);
			}
		}
	}

	return sudokuBoards;
}

static bool UpdatePossibilities(SudokuSolution& sol, Coord coord, u32 digit)
{
	for (u32 x = 0; x < Sudoku::boardSize; ++x)
	{
		DigitPossibility& possibilities = sol.boardTilePossibilities[coord.y][x];
		if (!possibilities.HasDigit(digit))
			continue;

		possibilities.RemoveDigit(digit);
		if (possibilities.IsEmpty())
			return false; // Impossible solution
		sol.coordQueue.push(CoordQueued({ x, coord.y }, possibilities));
	}

	for (u32 y = 0; y < Sudoku::boardSize; ++y)
	{
		DigitPossibility& possibilities = sol.boardTilePossibilities[y][coord.x];
		if (!possibilities.HasDigit(digit))
			continue;

		possibilities.RemoveDigit(digit);
		if (possibilities.IsEmpty())
			return false; // Impossible solution
		sol.coordQueue.push(CoordQueued({ coord.x, y }, possibilities));
	}

	assert(coord.x < Sudoku::boardSize && coord.y < Sudoku::boardSize);
	const u32 squareTileX = (coord.x / 3) * 3;
	const u32 squareTileY = (coord.y / 3) * 3;

	for (u32 xOffset = 0; xOffset < 3; ++xOffset)
	{
		for (u32 yOffset = 0; yOffset < 3; ++yOffset)
		{
			const u32 xCoord = squareTileX + xOffset;
			const u32 yCoord = squareTileY + yOffset;
			DigitPossibility& possibilities = sol.boardTilePossibilities[yCoord][xCoord];
			if (!possibilities.HasDigit(digit))
				continue;

			possibilities.RemoveDigit(digit);
			if (possibilities.IsEmpty())
				return false; // Impossible solution
			sol.coordQueue.push(CoordQueued({ xCoord, yCoord }, possibilities));
		}
	}

	return true;
}

static void InitCoordPriorityQueue(SudokuSolution& sol)
{
	assert(sol.coordQueue.empty()); // Should only be inited if empty
	for (u32 y = 0; y < Sudoku::boardSize; ++y)
	{
		for (u32 x = 0; x < Sudoku::boardSize; ++x)
		{
			const DigitPossibility& possibilities = sol.boardTilePossibilities[y][x];
			if (possibilities.IsEmpty())
				continue;

			sol.coordQueue.push(CoordQueued({ x, y }, possibilities));
		}
	}
}

static bool SolveBoardIter(SudokuSolution& sol)
{
	while (!sol.coordQueue.empty())
	{
		CoordQueued coordQueued = sol.coordQueue.top();
		const Coord coord = coordQueued.coord;
		sol.coordQueue.pop();

		if (sol.board.GetDigit(coord) != Sudoku::unsetDigit)
			continue;

		DigitPossibility& possibilities = sol.boardTilePossibilities[coord.y][coord.x];
		if (possibilities.PossibilityCount() == 1)
		{
			const u32 digit = possibilities.GetNumbers().front();
			possibilities.Clear();

			sol.board.SetDigit(coord, digit);
			const bool isStillValidSolution = UpdatePossibilities(sol, coord, digit);
			if (!isStillValidSolution)
				return false;
		}
		else
		{
			const std::vector<u32> nbsPossibilities = possibilities.GetNumbers();
			bool isStillValidSolution = false;
			for (u32 digitPossibilitity : nbsPossibilities)
			{
				SudokuSolution nextSol = sol;
				nextSol.board.SetDigit(coord, digitPossibilitity);
				nextSol.boardTilePossibilities[coord.y][coord.x].Clear();
				const bool isDigitPossible = UpdatePossibilities(nextSol, coord, digitPossibilitity);
				if (!isDigitPossible)
					continue;
				nextSol.coordQueue = CoordPriorityQueue{}; // Remove all next coords
				InitCoordPriorityQueue(nextSol);
				isStillValidSolution = SolveBoardIter(nextSol);
				if (isStillValidSolution)
				{
					sol.board = nextSol.board;
					break;
				}
			}
			if (!isStillValidSolution)
				return false;
		}
	}

	return true;
}

static void SolveBoard(Sudoku& board)
{
	SudokuSolution sol;
	sol.board = board;

	for (u32 y = 0; y < Sudoku::boardSize; ++y)
	{
		for (u32 x = 0; x < Sudoku::boardSize; ++x)
		{
			DigitPossibility& possibilities = sol.boardTilePossibilities[y][x];
			const u32 boardDigit = board.GetDigit(x, y);
			if (boardDigit == Sudoku::unsetDigit)
			{
				possibilities.SetToAllDigits();
			}
		}
	}

	for (u32 y = 0; y < Sudoku::boardSize; ++y)
	{
		for (u32 x = 0; x < Sudoku::boardSize; ++x)
		{
			const u32 boardDigit = board.GetDigit(x, y);
			if (boardDigit == Sudoku::unsetDigit)
				continue;

			const bool isPossibleSolution = UpdatePossibilities(sol, Coord{ x, y }, boardDigit);
			assert(isPossibleSolution);
		}
	}

	SolveBoardIter(sol);
	board = sol.board;
}

static u32 Solve(const char* filePath)
{
	std::vector<Sudoku> boards = ReadFile(filePath);

	u32 sumOfThreeFirstDigitsOfBoards = 0;
	for (Sudoku& board : boards)
	{
		SolveBoard(board);

		const u32 boardSum = 100 * board.GetDigit({ 0, 0 }) + 10 * board.GetDigit({ 1, 0 }) + board.GetDigit({ 2, 0 });
		sumOfThreeFirstDigitsOfBoards += boardSum;

		for (u32 y = 0; y < Sudoku::boardSize; ++y)
		{
			for (u32 x = 0; x < Sudoku::boardSize; ++x)
			{
				std::cout << board.GetDigit(x, y);
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	return sumOfThreeFirstDigitsOfBoards;
}

int main()
{
	constexpr const char* filePath = "resources/0096_sudoku.txt";
	const u32 sol = Solve(filePath);
	std::cout << "Solution 96: " << sol << std::endl;

	return 0;
}