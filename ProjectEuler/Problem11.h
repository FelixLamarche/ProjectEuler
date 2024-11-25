#pragma once

#include <vector>

typedef std::vector<std::vector<int>> Vec2D;

/// <summary>
/// Find the biggest product of N consecutive numbers in a MxM Grid of numbers
/// in either the up, down, left, right, or diagonal direction
/// </summary>
class Problem11
{
public:
	static int Solve(const Vec2D& nbs, const int consecutive);
};