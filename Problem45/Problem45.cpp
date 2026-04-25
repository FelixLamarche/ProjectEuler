// Problem 45 Triangular, Pentagonal, and Hexagonal
// Triangle number Tn = n*(n+1)/2
// Pentagonal Number Pn = n*(3n-1)/2
// Hexagonal number Hn = n*(2n - 1)
// T_285 = P_165 = H_143 = 40755
// Find the next triangle, pentagonal and hexagonal number

#include <iostream>

using int64 = long long;

#define LOGF(str, ...) do { print64f(str, __VA_ARGS__); } while(0)

static int64 TriangleNumber(int64 n)
{
	return n * (n + 1) / 2;
}

static int64 PentagonalNumber(int64 n)
{
	return n * (3 * n - 1) / 2;
}

static int64 HexagonalNumber(int64 n)
{
	return n * (2 * n - 1);
}

static int64 Solve()
{
	int64 triangleNumberIdx = 285;
	int64 pentagonalNumberIdx = 165;
	int64 hexagonalNumberIdx = 143;

	constexpr int64 baseNumber = 40755;
	int64 triangleNumber = baseNumber;
	int64 pentagonalNumber = baseNumber + 1;
	int64 hexagonalNumber = baseNumber + 2;

	while (triangleNumber != pentagonalNumber && triangleNumber != hexagonalNumber)
	{
		while (triangleNumber < pentagonalNumber || triangleNumber < hexagonalNumber)
		{
			triangleNumber = TriangleNumber(triangleNumberIdx++);
		}

		while (pentagonalNumber < triangleNumber || pentagonalNumber < hexagonalNumber)
		{
			pentagonalNumber = PentagonalNumber(pentagonalNumberIdx++);
		}

		while (hexagonalNumber < triangleNumber || hexagonalNumber < pentagonalNumber)
		{
			hexagonalNumber = HexagonalNumber(hexagonalNumberIdx++);
		}
	}
	return triangleNumber;
}

void main()
{
	const int64 solution = Solve();
	std::cout << "Problem 45 Solution :"<< solution << std::endl;
}

