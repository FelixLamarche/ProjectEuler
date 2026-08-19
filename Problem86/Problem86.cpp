// Problem 86: Cuboid Route

#include <format>
#include <iostream>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

// Returns the number of cuboids of shape Length x Depth x Height with dimensions below M, where Length <= Depth <= Height
// which have a shortest path from a corner vertex to its opposite corner vertex while following the faces be an integer amount
static u64 Solve(const u64 targetToReach)
{
	constexpr i64 safeMaxM = 1'000'000;

	u64 integerSolutionCount = 0;
	u64 length = 1;
	for (; length <= safeMaxM; length++)
	{
		for (u64 depth = 1; depth <= length; depth++)
		{
			for (u64 height = 1; height <= depth; height++)
			{
				// the three shortest path candiate
				const u64 path1Squared = (length + depth) * (length + depth) + height * height;
				const u64 path2Squared = (length + height) * (length + height) + depth * depth;
				const u64 path3Squared = (height + depth) * (height + depth) + length * length;

				const u64 shortestPathSquared = std::min(std::min(path1Squared, path2Squared), path3Squared);
				const u64 shortestPathLength = std::sqrt(shortestPathSquared);
				if (shortestPathLength * shortestPathLength == shortestPathSquared)
				{
					++integerSolutionCount;
				}
			}
		}

		if (integerSolutionCount > targetToReach)
			break;
	}

	return length;
}

int main()
{
	const u64 targetToReach = 1'000'000;
	const u64 sol = Solve(targetToReach);
	std::cout << "Solution 86: " << sol << std::endl;

	return 0;
}