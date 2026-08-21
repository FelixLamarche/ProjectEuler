// Problem 91: Right Triangles with Integer Coordinates

#include <array>
#include <format>
#include <iostream>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

struct Point
{
	int x;
	int y;
};

static int DotProduct(const Point& p0, const Point& p1)
{
	return p0.x * p1.x + p0.y * p1.y;
}

static int LengthSq(const Point& p)
{
	return p.x * p.x + p.y * p.y;
}

static bool FormsRightTriangle(const Point& p0, const Point& p1, const Point& p2)
{
	const Point p0ToP1 = { p1.x - p0.x, p1.y - p0.y };
	const Point p0ToP2 = { p2.x - p0.x, p2.y - p0.y };
	const Point p1ToP2 = { p2.x - p1.x, p2.y - p1.y };

	if (LengthSq(p0ToP1) == 0 || LengthSq(p0ToP2) == 0 || LengthSq(p1ToP2) == 0)
		return false;

	if (DotProduct(p0ToP1, p0ToP2) == 0 || DotProduct(p0ToP2, p1ToP2) == 0 || DotProduct(p0ToP1, p1ToP2) == 0)
		return true;
	return false;
}

static u64 Solve(const int maxCoord)
{
	u64 rightTriangleCount = 0;

	const Point p0{ 0, 0 };

	Point p1{ 0, 0 };
	Point p2{ 0, 0 };
	for (p1.x = 0; p1.x <= maxCoord; ++p1.x)
	{
		p1.y = 0;
		for (; p1.y <= maxCoord; ++p1.y)
		{
			p2.x = p1.x;
			for (; p2.x <= maxCoord; ++p2.x)
			{
				p2.y = p1.x == p2.x ? p1.y + 1 : 0;
				for (; p2.y <= maxCoord; ++p2.y)
				{
					if (FormsRightTriangle(p0, p1, p2))
						++rightTriangleCount;
				}
			}
		}
	}

	return rightTriangleCount;
}

int main()
{
	const int maxCoord = 50;
	const u64 sol = Solve(maxCoord);
	std::cout << "Solution 91: " << sol << std::endl;

	return 0;
}