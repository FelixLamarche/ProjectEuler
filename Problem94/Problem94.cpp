// Problem 94 : Almost Equilateral Triangles

#include <cassert>
#include <format>
#include <iostream>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

static u64 Solve(u64 upperBoundPerimeter)
{
	u64 perimeterSum = 0;

	const u64 maxSideLength = upperBoundPerimeter / 3 + 1;
	for (u64 a = 3; a <= maxSideLength; a += 2)
	{
		const u64 b = a;
		u64 c = a - 1;
		for (u32 i = 0; i < 2; ++i, c += 2)
		{
			// right-triangle to get height
			assert(c % 2 == 0);
			const u64 side = c / 2;
			const u64 h2 = a * a - side * side;
			const u64 h = sqrt(h2);
			if (h * h == h2)
			{
				assert(c % 2 == 0, "We get an integer area only if h or c is even");
				perimeterSum += a + b + c;
			}
		}
	}

	return perimeterSum;
}

int main()
{
	const u64 upperBound = 1'000'000'000;
	const u64 sol = Solve(upperBound);
	std::cout << "Solution 94: " << sol << std::endl;

	return 0;
}