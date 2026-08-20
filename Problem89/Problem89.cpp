// Problem 89: Roman Numerals

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

struct RomanNumeral
{
	char chr;
	u32 value;
};

static constexpr RomanNumeral romanOne{ 'I', 1 };
static constexpr RomanNumeral romanFive{ 'V', 5 };
static constexpr RomanNumeral romanTen{ 'X', 10 };
static constexpr RomanNumeral romanFifty{ 'L', 50 };
static constexpr RomanNumeral romanHundred{ 'C', 100 };
static constexpr RomanNumeral romanFiveHundred{ 'D', 500 };
static constexpr RomanNumeral romanThousand{ 'M', 1000 };

static std::string MinimalRomanNumeral(u64 nb)
{
	// ROMAN NUMERAL RULES:
	// Numerals must be arranged in descending order of size.
	// M, C, and X cannot be equalled or exceeded by smaller denominations.
	// D, L, and V can each only appear once.
	// Only one I, X, and C can be used as the leading numeral in part of a subtractive pair.
	// I can only be placed before V and X.
	// X can only be placed before L and C.
	// C can only be placed before D and M.

	std::string str;
	while (nb >= romanThousand.value)
	{
		str.push_back(romanThousand.chr);
		nb -= romanThousand.value;
	}

	if (nb >= 900)
	{
		str.push_back(romanHundred.chr);
		str.push_back(romanThousand.chr);
		nb -= 900;
	}

	if (nb >= romanFiveHundred.value)
	{
		str.push_back(romanFiveHundred.chr);
		nb -= romanFiveHundred.value;
	}

	if (nb >= 400)
	{
		str.push_back(romanHundred.chr);
		str.push_back(romanFiveHundred.chr);
		nb -= 400;
	}

	while (nb >= romanHundred.value)
	{
		str.push_back(romanHundred.chr);
		nb -= romanHundred.value;
	}

	if (nb >= 90)
	{
		str.push_back(romanTen.chr);
		str.push_back(romanHundred.chr);
		nb -= 90;
	}

	if (nb >= romanFifty.value)
	{
		str.push_back(romanFifty.chr);
		nb -= romanFifty.value;
	}

	if (nb >= 40)
	{
		str.push_back(romanTen.chr);
		str.push_back(romanFifty.chr);
		nb -= 40;
	}

	while (nb >= romanTen.value)
	{
		str.push_back(romanTen.chr);
		nb -= romanTen.value;
	}

	if (nb >= 9)
	{
		str.push_back(romanOne.chr);
		str.push_back(romanTen.chr);
		nb -= 9;
	}

	if (nb >= romanFive.value)
	{
		str.push_back(romanFive.chr);
		nb -= romanFive.value;
	}

	if (nb >= 4)
	{
		str.push_back(romanOne.chr);
		str.push_back(romanFive.chr);
		nb -= 4;
	}

	while (nb >= romanOne.value)
	{
		str.push_back(romanOne.chr);
		nb -= romanOne.value;
	}

	return str;
}

static u64 ReadRomanNumeral(const std::string& romanNb)
{
	u64 nb = 0;
	for (u32 chrIdx = 0; chrIdx < romanNb.size(); ++chrIdx)
	{
		const char curChar = romanNb[chrIdx];
		const char nextChar = chrIdx + 1 < romanNb.size() ? romanNb[chrIdx + 1] : ' ';

		if (curChar == romanThousand.chr)
		{
			nb += romanThousand.value;
		}
		else if (curChar == romanFiveHundred.chr)
		{
			nb += romanFiveHundred.value;
		}
		else if (curChar == romanHundred.chr)
		{
			if (nextChar == romanThousand.chr)
			{
				nb += romanThousand.value - romanHundred.value;
				++chrIdx;
			}
			else if (nextChar == romanFiveHundred.chr)
			{
				nb += romanFiveHundred.value - romanHundred.value;
				++chrIdx;
			}
			else
			{
				nb += romanHundred.value;
			}
		}
		else if (curChar == romanFifty.chr)
		{
			nb += romanFifty.value;
		}
		else if (curChar == romanTen.chr)
		{
			if (nextChar == romanHundred.chr)
			{
				nb += romanHundred.value - romanTen.value;
				++chrIdx;
			}
			else if (nextChar == romanFifty.chr)
			{
				nb += romanFifty.value - romanTen.value;
				++chrIdx;
			}
			else
			{
				nb += romanTen.value;
			}
		}
		else if (curChar == romanFive.chr)
		{
			nb += romanFive.value;
		}
		else if (curChar == romanOne.chr)
		{
			if (nextChar == romanTen.chr)
			{
				nb += romanTen.value - romanOne.value;
				++chrIdx;
			}
			else if (nextChar == romanFive.chr)
			{
				nb += romanFive.value - romanOne.value;
				++chrIdx;
			}
			else
			{
				nb += romanOne.value;
			}
		}
	}
	return nb;
}

static std::vector<std::string> ReadFile(const char* fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cout << "Could not open file: " << fileName << std::endl;
		return {};
	}

	std::vector<std::string> romanStrs;

	std::string readStr;
	while (std::getline(file, readStr))
		romanStrs.push_back(std::move(readStr));

	return romanStrs;
}

static u64 Solve(const char* fileName)
{
	std::vector<std::string> romanNumerals = ReadFile(fileName);
	u64 characterDiff = 0;
	for (const std::string& romanStr : romanNumerals)
	{
		const u64 nbValue = ReadRomanNumeral(romanStr);
		const std::string optimalRomanStr = MinimalRomanNumeral(nbValue);

		assert(optimalRomanStr.size() <= romanStr.size());
		characterDiff += romanStr.size() - optimalRomanStr.size();
	}

	return characterDiff;
}

int main()
{
	constexpr const char* fileName = "resources/0089_roman.txt";
	const u64 sol = Solve(fileName);
	std::cout << "Solution 89: " << sol << std::endl;

	return 0;
}
