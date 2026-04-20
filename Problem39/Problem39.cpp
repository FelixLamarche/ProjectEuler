// Problem 39 Integer Right Triangles
// If p is the perimeter of a right-angle triangle with integrals lengths of { a, b, c }
// Then, there are 3 solutions for p = 120, { 20, 48, 52 } { 24, 45, 51 }, { 30, 40, 50 }
// For which value of p <= 1000, is the number of solutions maximized ?

#include <algorithm>
#include <iostream>
#include <vector>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(false)

static int Solve(const int perimeterUpperBound)
{
	std::vector<int> perimetersCount(perimeterUpperBound + 1, 0);

	const int sideLengthMax = perimeterUpperBound / 2;
	for (int a = 2; a < sideLengthMax; ++a)
	{
		for (int b = 2; b <= a; ++b)
		{
			const int cSq = a * a + b * b;
			const int cSqRoot = std::sqrt(cSq);
			if (cSqRoot * cSqRoot != cSq)
				continue;

			const int p = cSqRoot + a + b;
			if (p >= perimetersCount.size())
				break;

			LOGF("p:%i { %i, %i, %i }\n", p, a, b, cSqRoot);
			++perimetersCount[p];
		}
	}

	auto itMaxElement = std::max_element(perimetersCount.cbegin(), perimetersCount.cend());
	const int maxElementIndex = std::distance(perimetersCount.cbegin(), itMaxElement);

	return maxElementIndex;
}

void main()
{
	constexpr int pBound = 1'000;
	const int solution = Solve(pBound);
	std::cout << "Problem 39: " << solution << std::endl;
}