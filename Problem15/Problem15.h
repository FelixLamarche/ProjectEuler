#pragma once


// Calculate The number of ways to traverse a M x N path
// Where you may only go right or go down.
// Start at the top-left corner and you go to the bottom right corner
// The solutions for N x M is a (N+M) choose M problem.
// You advance for N+M steps in total and you choose M of those steps
class Problem15
{
public:
	static long long Solve(int N, int M);
	static long long Degree(long long a, long long k, long long p);
	static long long NChooseKModP(int n, int k, int p);
};
