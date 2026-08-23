// Problem 97 : Large Non-Mersene Prime

#include <format>
#include <iostream>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

static u64 Solve()
{
	constexpr u64 lastDigitsModulo = 10000000000;
	u64 nb = 28433;
	constexpr u64 twosExponent = 7830457;
	for (u64 curTwoExponent = 1; curTwoExponent <= twosExponent; ++curTwoExponent)
	{
		nb = (nb * 2) % lastDigitsModulo;
	}
	return nb + 1;
}

int main()
{
	const u64 sol = Solve();
	std::cout << "Solution 97: " << sol << std::endl;

	return 0;
}