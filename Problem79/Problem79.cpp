// Problem 79: Passcode Derivation

#include <format>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <vector>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;

static void SolveIter(
	std::map<char, std::set<char>>& charsToPrecedingChars,
	std::string& curSol,
	std::string& bestSolution,
	int& bestSolutionLength)
{
	// Base case
	if (charsToPrecedingChars.empty())
	{
		if (curSol.size() < bestSolutionLength)
		{
			bestSolution = curSol;
			bestSolutionLength = bestSolution.size();
		}
		return;
	}

	std::vector<int> charsOfSolution;
	int curPrecedingCount = 0;
	while (charsOfSolution.empty())
	{
		for (const auto& [chr, chrsPreceding] : charsToPrecedingChars)
		{
			if (chrsPreceding.size() == curPrecedingCount)
				charsOfSolution.push_back(chr);
		}
	}

	std::vector<char> listsModified;
	for (const char nextChr : charsOfSolution)
	{
		// update all current strings to use the current symbol
		curSol.push_back(nextChr);
		for (auto& [chr, chrsPreceding] : charsToPrecedingChars)
		{
			chrsPreceding.erase(nextChr);
			listsModified.push_back(chr);
		}
		std::set<char> removedSet = std::move(charsToPrecedingChars[nextChr]);
		charsToPrecedingChars.erase(nextChr);

		SolveIter(charsToPrecedingChars, curSol, bestSolution, bestSolutionLength);

		// Undo 
		charsToPrecedingChars[nextChr] = std::move(removedSet);
		for (const char chrListModified : listsModified)
			charsToPrecedingChars[chrListModified].insert(nextChr);
		curSol.pop_back();

		listsModified.clear();
	}
}

static std::string Solve(const char* fileName)
{
	std::vector<std::string> strings;

	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cout << "Could not Read File." << std::endl;
		return "";
	}

	std::string readStr;
	while (std::getline(file, readStr))
		strings.push_back(std::move(readStr));

	std::map<char, std::set<char>> charsToCharsPreceding;
	for (int i = 0; i < strings.size(); ++i)
	{
		const std::string& str = strings[i];
		for (int chrIdx = 0; chrIdx < str.size(); ++chrIdx)
		{
			const char chr = strings[i][chrIdx];
			std::set<char>& charsPreceding = charsToCharsPreceding[chr];
			for (int precedingChrIdx = 0; precedingChrIdx < chrIdx; ++precedingChrIdx)
			{
				charsPreceding.insert(strings[i][precedingChrIdx]);
			}
		}
	}

	for (const auto& [chr, chrsPreceding] : charsToCharsPreceding)
	{
		std::cout << chr << ": [";
		for (char chrPreceding : chrsPreceding)
			std::cout << chrPreceding << ", ";
		std::cout << "]" << std::endl;
	}

	std::string sol = "";
	std::string curStr = "";
	int solLength = std::numeric_limits<int>::max();
	SolveIter(charsToCharsPreceding, curStr, sol, solLength);
	return sol;
}

int main()
{
	constexpr const char* fileName = "resources/0079_keylog.txt";
	const std::string sol = Solve(fileName);
	std::cout << "Solution 79: " << sol << std::endl;

	return 0;
}