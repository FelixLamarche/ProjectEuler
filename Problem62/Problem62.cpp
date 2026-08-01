// Problem 62: Cubic Permutations

#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned long;
using u64 = unsigned long long;

using NumberDigits = u64;

static u64 Cube(const u64 nb)
{
	return nb * nb * nb;
}

static void ToDigitsArray(NumberDigits& digits, u64 nb)
{
	std::array<u8, 10> digitsArray{ 0 };

	while (nb > 0)
	{
		const u8 digit = nb % 10;
		digitsArray[digit]++;
		nb /= 10;
	}

	digits = 0;
	for (int digit = 1; digit < digitsArray.size(); digit++)
	{
		for (int i = 0; i < digitsArray[digit]; ++i)
			digits = digits * 10 + digit;
	}

	// put 0s at the end of the number so they are significant 
	for (int i = 0; i < digitsArray[0]; ++i)
		digits *= 10;
}

static u64 Solve(const u32 permutationCount)
{
	using DigitsPermutationMap = std::unordered_map<NumberDigits, std::vector<u64>>;

	const std::vector<u64>* foundPermutations = nullptr;

	DigitsPermutationMap map;
	u64 nb = 0;
	while (true)
	{
		nb++;

		const u64 cubedNb = Cube(nb);
		NumberDigits digitsArray = 0;
		ToDigitsArray(digitsArray, cubedNb);

		std::vector<u64>& permutations = map[digitsArray];
		permutations.push_back(cubedNb);

		if (permutations.size() >= permutationCount)
		{
			foundPermutations = &permutations;
			break;
		}
	}

	const u64 minCube = *std::min_element(foundPermutations->begin(), foundPermutations->end());
	return minCube;
}

void main()
{
	constexpr u32 permutationCount = 5;
	const u64 sol = Solve(permutationCount);
	std::cout << "Solution 62: " << sol << std::endl;
}
