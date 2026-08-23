// Problem 99 : Largest Exponential

#include <cassert>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

struct Power {
	u64 base;
	u64 exponent;
};

static std::vector<Power> ReadPowersInFile(const char* filePath)
{
	std::ifstream fileStream(filePath);
	if (!fileStream.is_open())
	{
		std::cout << "Could not open file at: " << filePath << std::endl;
		return {};
	}

	std::vector<Power> powers;
	std::string readStr;
	while (std::getline(fileStream, readStr))
	{
		assert(!readStr.empty());
		const int idxSeperator = readStr.find_first_of(',');
		assert(idxSeperator > 0);

		const std::string& baseStr = readStr.substr(0, idxSeperator);
		const std::string& expStr = readStr.substr(idxSeperator + 1, readStr.size() - idxSeperator - 1);

		Power& power = powers.emplace_back();
		power.base = std::stoull(baseStr);
		power.exponent = std::stoull(expStr);
	}

	return powers;
}

static u64 Solve(const char* filePath)
{
	std::vector<Power> powers = ReadPowersInFile(filePath);

	u64 largestNbIdx = 0;
	double largestNbResult = 0;
	for (u64 i = 0; i < powers.size(); ++i)
	{
		const Power& power = powers[i];
		// n^p => p* log(n)

		const double result = power.exponent * std::log(power.base);
		if (result > largestNbResult)
		{
			largestNbResult = result;
			largestNbIdx = i;
		}
	}

	// Add 1 to not start counting on 0
	return largestNbIdx + 1;
}

int main()
{
	constexpr const char* filePath = "resources/0099_base_exp.txt";
	const u64 sol = Solve(filePath);
	std::cout << "Solution 99: " << sol << std::endl;

	return 0;
}