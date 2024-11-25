#pragma once

/// <summary>
/// Return the smallest number that is evenly divisible by every number below from 1 to N.
/// </summary>
class Problem5 {
public:
	static long long Solve(int n);
private:
	static bool IsPrime(int n);
};