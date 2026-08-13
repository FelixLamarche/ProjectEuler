// Problem 67 Maximum Path Sum II

#include <assert.h>
#include <format>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <sstream>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

static void ReadFile(std::vector<std::vector<u32>>& rowsOfNbs)
{
	std::ifstream file;
	file.open("0067_triangle.txt");

	if (!file.is_open())
	{
		std::cout << "cannot open file ." << std::endl;
		return;
	}

	std::string lineStr;
	while (std::getline(file, lineStr))
	{
		std::istringstream lineStream(lineStr);
		std::vector<u32>& nbs = rowsOfNbs.emplace_back();

		u32 nb;
		while (lineStream >> nb)
			nbs.push_back(nb);
	}
	file.close();
}

static u32 Solve()
{
	// Row[0] has 1 nb, Row[1] has 2, etc.
	std::vector<std::vector<u32>> rowsOfNbs;
	ReadFile(rowsOfNbs);
	
	for (u32 rowIdx = rowsOfNbs.size() - 1; rowIdx > 0; --rowIdx)
	{
		std::vector<u32>& upperRow = rowsOfNbs[rowIdx - 1];
		const std::vector<u32>& lowerRow = rowsOfNbs[rowIdx];

		for (u32 nbIdx = 0; nbIdx < upperRow.size(); ++nbIdx)
		{
			upperRow[nbIdx] += std::max(lowerRow[nbIdx], lowerRow[nbIdx + 1]);
		}
	}

	// top element which is biggest sum
	return rowsOfNbs[0][0];
}

void main()
{
	const u32 sol = Solve();
	std::cout << "Solution 67: " << sol << std::endl;
}