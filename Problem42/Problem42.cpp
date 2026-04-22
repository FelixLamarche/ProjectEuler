// Problem 42 Coded Triangle Numbers
// A triangle number is a number in the sequence { 1, 3, 6, 10, 15, 21, ... }
// Where the nth triangle number = 1/2 * n * (n + 1)
// Words can be converted to a value by summing the value of its characters from the words.txt file
// SKY = 19 + 11 + 25 = 55, so it is a triangle number word
// How many words are triangle numbers?

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(false);

static bool IsTriangleNumber(int nb)
{
	// Triangle numbers follow the sequence of n_i+1 = n + i
	// Where the nth plus 1 number in the sequence equals the nth number + n
	int sum = 0;
	int increment = 1;
	while (sum < nb)
	{
		sum += increment;
		if (nb == sum)
			return true;
		++increment;
	}
	return false;
}

static int WordToValue(const char* word)
{
	int sum = 0;
	int i = 0;
	while (char chr = word[i++])
	{
		if (chr < 'A' || chr > 'Z')
			continue;
		const int chrValue = chr - 'A' + 1;
		sum += chrValue;
	}

	return sum;
}

static int Solve()
{
	constexpr const char* wordsPath = "words.txt";

	if (!std::filesystem::exists(wordsPath))
	{
		LOGF("Could not find file at path: %s", wordsPath);
		return 0;
	}

	std::ifstream inputStream = std::ifstream(wordsPath);

	int triangleWordCount = 0;
	std::string s;
	while (std::getline(inputStream, s, ','))
	{
		const int wordValue = WordToValue(s.c_str());
		if (IsTriangleNumber(wordValue))
			triangleWordCount++;
	}

	return triangleWordCount;
}

void main()
{
	const int solution = Solve();
	std::cout << "Problem 42 Solution: " << solution << std::endl;
}
