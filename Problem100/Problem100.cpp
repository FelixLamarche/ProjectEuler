// Problem 100 : Arranged Probability

#include <cassert>
#include <format>
#include <iostream>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

static u64 Solve(const u64 minBound)
{
	// Solve (n / T) * ( (n - 1) / (t - 1)) = 1 / 2
	// rearrange to 2n(n - 1) - t^2 - t = 1 / 2
	// to 2(n^2 - n + 1/4 - 1/4) - (t^2 - t + 1/4 - 1/4) = 1 /2
	// to 2(n - 1/2)^2 - (t - 1/2)^2 - 1/4 = 0
	// Substitute u/2 = n - 1/2, v/2 = t - 1/2
	// 2(u/2)^2 - (v/2)^2 - 1/4 = 0
	// u^2/2 - v^2/4 - 1/4 = 0
	// 2u^2 - v^2 = 1
	// v^2 - 2u^2 = -1
	// Fundamental solution = (1, 1) => 1^2 - 2*(1^2) = -1
	// Diophantine equation (Pell's equation)
	// Recurrence formula:
	// for u_n, v_n, we only want odd n, as they are those which will give solutions = -1, even will equal 1
	// and we multiply (1 + sqrt(2)*1), from (u_1 + sqrt(d)*v_n)
	// and we multiply by (1+ sqrt(2)*1)^2 = (3 + 2*sqrt(2)) 
	// Then multiply that by the fundamental equation:
	// (1*v - sqrt(2)*u) (3 + 2*sqrt(2)) = 3v + 2*sqrt(2)v + 3*sqrt(2)*u + 4u
	// = (3v + 4u) + sqrt(2)*(2v + 3u)
	// so v_k_1 = 3v_k + 4u_k
	// u_k_1 = 2v_k + 3u_k
	//
	// v^2 - 2u^2 = -1
	// v = 2t - 1
	// u = 2n - 1
	constexpr u64 u1 = 1;
	constexpr u64 v1 = 1;

	u64 u = u1;
	u64 v = v1;

	u64 nbDiscs = 1;
	while (nbDiscs <= minBound)
	{
		const u64 nextU = 2 * v + 3 * u;
		const u64 nextV = 3 * v + 4 * u;
		u = nextU;
		v = nextV;
		nbDiscs = (v + 1) / 2;
	}

	return (u + 1) / 2;
}

int main()
{
	constexpr u64 minBound = 1e12;
	const u64 sol = Solve(minBound);
	std::cout << "Solution 100: " << sol << std::endl;

	return 0;
}