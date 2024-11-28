/// <summary>
/// Find and return the maximal sum of the path in a triangular set of rows of numbers:
/// example input:
/// 1
/// 4
/// 3      (Start of triangle here)
/// 7 4
/// 2 4 6
/// 8 5 9 3
/// </summary>

#include <iostream>
#include <vector>

typedef typename std::vector<std::vector<int>> Vec2DInt;

static int Solve(const Vec2DInt& nbs)
{
	std::vector<int> sums(nbs.size() + 1, 0);

	for (size_t i = nbs.size(); i > 0; i--)
	{
		const std::vector<int>& row = nbs[i - 1];
		
		for (size_t j = 0; j < row.size(); j++)
		{
			sums[j] = std::max(sums[j], sums[j + 1]) + row[j];
		}
	}

	return sums[0];
}

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++)
	{
		int N;
		std::cin >> N;

		Vec2DInt nbs;
		nbs.reserve(N);
		for (size_t j = 0; j < N; j++)
		{
			std::vector<int> row;
			row.reserve(j + 1);
			for (size_t k = 0; k < j + 1; k++)
			{
				int nb;
				std::cin >> nb;
				row.push_back(nb);
			}
			nbs.push_back(row);
		}

		std::cout << Solve(nbs) << std::endl;
	}
	return 0;
}