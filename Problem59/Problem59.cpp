// Problem 59: XOR Decryption
#include <format>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

using u64 = unsigned long long;
using u32 = unsigned long;

static u32 Solve()
{
	std::ifstream file;
	file.open("resources/0059_cipher.txt");

	if (!file.is_open())
	{
		std::cout << "cannot open file." << std::endl;
		return 0;
	}

	std::vector<char> chars;
	std::string str;
	while (std::getline(file, str, ','))
	{
		int nb = std::atoi(str.c_str());
		chars.push_back(nb);
	}

	// This found out the correct XOR to use which was 'exp'
	if (false)
	{
		for (char chr1 = 'a'; chr1 <= 'z'; chr1++)
		{
			for (char chr2 = 'a'; chr2 <= 'z'; chr2++)
			{
				for (char chr3 = 'a'; chr3 <= 'z'; chr3++)
				{
					std::vector<char> xorChars;
					xorChars.reserve(chars.size());

					const char chrsXORop[]{ chr1, chr2, chr3 };
					const u32 chrsXORopCount = 3;
					for (u32 chrIdx = 0; chrIdx < chars.size(); ++chrIdx)
					{
						xorChars.push_back(static_cast<char>(chars[chrIdx] ^ chrsXORop[chrIdx % chrsXORopCount]));
					}

					u32 spaceCount = std::count(xorChars.cbegin(), xorChars.cend(), ' ');
					float spaceRatio = static_cast<float>(spaceCount) / xorChars.size();
					if (spaceRatio > 0.1f)
					{
						std::cout << chr1 << chr2 << chr3 << std::endl;
						for (char chr : xorChars)
						{
							std::cout << chr;
						}
						std::cout << '\n' << std::endl;
					}
				}
			}
		}
	}

	// found out the xor key was 'exp'
	const char chrsXORop[]{ 'e', 'x', 'p' };
	const u32 chrsXORopCount = 3;

	u32 asciiSum = 0;
	for (u32 chrIdx = 0; chrIdx < chars.size(); ++chrIdx)
	{
		const char xorChar = static_cast<char>(chars[chrIdx] ^ chrsXORop[chrIdx % chrsXORopCount]);
		asciiSum += xorChar;
	}

	return asciiSum;
}

void main()
{
	const u32 sol = Solve();
	std::cout << "Solution 59: " << sol << std::endl;
}
