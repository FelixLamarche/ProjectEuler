#include "Problem11.h"

#include <numeric>

int Problem11::Solve(const Vec2D& nbs, const int consecutive)
{
	int biggest = 0;

	for (size_t j = 0; j < nbs.size(); j++)
	{
		for (size_t i = 0; i < nbs[j].size(); i++)
		{
			// Horizontal (right ,left)
			if (consecutive + i <= nbs[j].size())
			{
				int cur = 1;
				for (int k = 0; k < consecutive; k++)
				{
					cur *= nbs[j][i + k];
				}

				biggest = std::max(biggest, cur);
			}

			// Vertical (up, down)
			if (consecutive + j <= nbs.size())
			{
				int cur = 1;
				for (int k = 0; k < consecutive; k++)
				{
					cur *= nbs[j + k][i];
				}
				biggest = std::max(biggest, cur);
			}

			// Diagonal top-left to bottom-right
			if (consecutive + j <= nbs.size() && consecutive + i <= nbs[j].size())
			{
				int cur = 1;
				for (int k = 0; k < consecutive; k++)
				{
					cur *= nbs[j + k][i + k];
				}
				biggest = std::max(biggest, cur);
			}

			// Diagonal top-right to bottom-left
			if (consecutive + j <= nbs.size() && i >= consecutive - 1)
			{
				int cur = 1;
				for (int k = 0; k < consecutive; k++)
				{
					cur *= nbs[j + k][i - k];
				}
				biggest = std::max(biggest, cur);
			}
		}
	}
	return biggest;
}
