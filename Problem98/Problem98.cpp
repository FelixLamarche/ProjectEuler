// Problem 98 : Anagramic Squares

#include <algorithm>
#include <cassert>
#include <format>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

static bool IsSquareNumber(const u64 nb)
{
	const u64 sqrtNb = std::sqrt(nb);
	return sqrtNb * sqrtNb == nb;
}

static std::string SortedString(const std::string& str)
{
	std::vector<char> charsSorted;
	for (const char chr : str)
		charsSorted.push_back(chr);
	std::sort(charsSorted.begin(), charsSorted.end());
	std::string sortedStr(charsSorted.begin(), charsSorted.end());
	return sortedStr;
}

static std::vector<std::string> ReadWordsInFile(const char* filePath)
{
	std::ifstream fileStream(filePath);
	if (!fileStream.is_open())
	{
		std::cout << "Could not open file at: " << filePath << std::endl;
		return {};
	}

	std::vector<std::string> words;
	std::string readStr;
	while (std::getline(fileStream, readStr, ','))
	{
		assert(readStr.size() > 2);
		words.push_back(readStr.substr(1, readStr.size() - 2));
	}

	return words;
}

static std::vector<std::vector<std::string>> GetAnagramLists(const std::vector<std::string>& words)
{
	std::unordered_map<std::string, std::vector<std::string>> anagramToWords;
	for (const std::string& word : words)
	{
		std::string anagramSorted = SortedString(word);
		std::vector<std::string>& anagrams = anagramToWords[anagramSorted];
		anagrams.push_back(word);
	}

	std::vector<std::vector<std::string>> anagramList;
	for (auto& [anagram, anagrams] : anagramToWords)
	{
		if (anagrams.size() == 2)
			anagramList.push_back(std::move(anagrams));
	}

	return anagramList;
}

static u64 GetLargestNbAnagram(const std::vector<std::string>& nbAnagrams, const std::vector<std::string>& wordList)
{
	assert(wordList.size() == 2); // only handle pairs for now
	const std::string& word1 = wordList[0];
	const std::string& word2 = wordList[1];

	u64 largestSquare = 0;
	for (u32 nbIdx1 = 0; nbIdx1 < nbAnagrams.size(); ++nbIdx1)
	{
		const std::string& nbStr1 = nbAnagrams[nbIdx1];

		std::unordered_map<char, char> charsToNb;
		std::unordered_map<char, char> nbToChars;

		bool wordChrsMatchesNbChrs = true;
		assert(nbStr1.size() == word1.size());
		for (u32 chrIdx = 0; chrIdx < nbStr1.size(); ++chrIdx)
		{
			const char wordChr = word1[chrIdx];
			const char nbChr = nbStr1[chrIdx];
			if (charsToNb.contains(wordChr))
			{
				wordChrsMatchesNbChrs = wordChrsMatchesNbChrs && charsToNb[wordChr] == nbChr;
			}
			else
			{
				charsToNb[wordChr] = nbChr;
			}

			if (nbToChars.contains(nbChr))
			{
				wordChrsMatchesNbChrs = wordChrsMatchesNbChrs && nbToChars[nbChr] == wordChr;
			}
			else
			{
				nbToChars[nbChr] = wordChr;
			}

			if (!wordChrsMatchesNbChrs)
				break;
		}

		if (!wordChrsMatchesNbChrs)
			continue;

		for (u32 nbIdx2 = 0; nbIdx2 < nbAnagrams.size(); ++nbIdx2)
		{
			if (nbIdx1 == nbIdx2)
				continue;

			const std::string& nbStr2 = nbAnagrams[nbIdx2];
			for (u32 chrIdx = 0; chrIdx < nbStr2.size(); ++chrIdx)
			{
				const char wordChr = word2[chrIdx];
				const char nbChr = nbStr2[chrIdx];
				if (charsToNb.contains(wordChr))
				{
					wordChrsMatchesNbChrs = wordChrsMatchesNbChrs && charsToNb[wordChr] == nbChr;
				}
				else
				{
					charsToNb[wordChr] = nbChr;
				}

				if (nbToChars.contains(nbChr))
				{
					wordChrsMatchesNbChrs = wordChrsMatchesNbChrs && nbToChars[nbChr] == wordChr;
				}
				else
				{
					nbToChars[nbChr] = wordChr;
				}

				if (!wordChrsMatchesNbChrs)
					break;
			}

			if (wordChrsMatchesNbChrs)
			{
				const u64 nb1 = std::stoull(nbStr1);
				const u64 nb2 = std::stoull(nbStr2);
				largestSquare = std::max(largestSquare, nb1);
				largestSquare = std::max(largestSquare, nb2);
			}
		}
	}

	return largestSquare;
}

static u64 Solve(const char* filePath)
{
	std::vector<std::string> words = ReadWordsInFile(filePath);
	std::vector<std::vector<std::string>> anagramLists = GetAnagramLists(words);
	std::unordered_map<u32, std::unordered_map<std::string, std::vector<std::string>>> digitLengthToSquareDigitsAnagrams;

	// Get digits anagrams as strings
	{
		u32 maxLength = 0;
		for (const std::vector<std::string>& anagramList : anagramLists)
		{
			for (const std::string& str : anagramList)
				maxLength = std::max(maxLength, static_cast<u32>(str.size()));
		}
		u32 nb = 0;
		u32 nbSquare = 0;
		while (true)
		{
			nb++;
			nbSquare = nb * nb;

			std::string nbSquareStr = std::to_string(nbSquare);
			if (nbSquareStr.length() > maxLength)
				break;

			std::unordered_map<std::string, std::vector<std::string>>& nbAnagramToNumbers = digitLengthToSquareDigitsAnagrams[nbSquareStr.size()];
			const std::string sortedNbSquareStr = SortedString(nbSquareStr);
			std::vector<std::string>& nbAnagrams = nbAnagramToNumbers[sortedNbSquareStr];
			nbAnagrams.push_back(std::move(nbSquareStr));
		}
	}

	u64 largestSquareNbOfAnagramPair = 0;

	for (const std::vector<std::string>& anagramList : anagramLists)
	{
		const u32 anagramLength = anagramList.front().size();
		const std::unordered_map<std::string, std::vector<std::string>>& nbAnagramToNumbers = digitLengthToSquareDigitsAnagrams[anagramLength];

		for (const auto& [sortedNbStr, nbAnagrams] : nbAnagramToNumbers)
		{
			const u64 largestPoppedSquare = GetLargestNbAnagram(nbAnagrams, anagramList);
			largestSquareNbOfAnagramPair = std::max(largestSquareNbOfAnagramPair, largestPoppedSquare);
		}
	}

	return largestSquareNbOfAnagramPair;
}

int main()
{
	constexpr const char* filePath = "resources/0098_words.txt";
	const u64 sol = Solve(filePath);
	std::cout << "Solution 98: " << sol << std::endl;

	return 0;
}