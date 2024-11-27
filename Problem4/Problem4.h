#pragma once

/// <summary>
/// Find the largest palindromic number from two 3-digit numbers which is less than N.
/// </summary>
class Problem4 {
public:
	static int Solve(int limit);
private:
	static inline bool IsPalindromic(int nb);
};
