// Problem 85: Counting Rectangles

#include <format>
#include <iostream>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

static i64 TriangleNumber(i64 n)
{
	return n * (n + 1) / 2;
}


static i64 RectangleCombinations(i64 n, i64 m)
{
	return TriangleNumber(n) * TriangleNumber(m);
}

static i64 Solve(const i64 targetRectangleCount)
{
	constexpr i64 safeMaxN = 1'000'000;
	constexpr i64 safeMaxM = 1'000'000;

	i64 bestN = 0;
	i64 bestM = 0;
	i64 bestDiff = targetRectangleCount;
	for (i64 n = 1; n < safeMaxN; ++n)
	{
		i64 m = 1;
		for (; m < safeMaxM; ++m)
		{
			const i64 rectangleCount = RectangleCombinations(n, m);
			const i64 diff = std::abs(targetRectangleCount - rectangleCount);
			if (diff < bestDiff)
			{
				bestN = n;
				bestM = m;
				bestDiff = diff;
			}

			if (rectangleCount > targetRectangleCount)
				break;
		}

		if (m == 1)
			break;
	}

	// return the area of the closest solution
	return bestN * bestM;
}

int main()
{
	const i64 targetRectangleCount = 2'000'000;
	const i64 sol = Solve(targetRectangleCount);
	std::cout << "Solution 85: " << sol << std::endl;

	return 0;
}