// ProjectEuler.cpp : Defines the entry point for the application.
//
#include "Problem11.h"

#include <iostream>
#include <string>
#include <vector>

int main()
{
	constexpr int size = 20;
    constexpr int K = 4;

	std::vector<std::vector<int>> grid(size, std::vector<int>(size));
    for (int grid_i = 0; grid_i < size; grid_i++) {
        for (int grid_j = 0; grid_j < size; grid_j++) {
            std::cin >> grid[grid_i][grid_j];
        }
    }

    std::cout << Problem11::Solve(grid, K) << std::endl;

	return 0;
}
