// ProjectEuler.cpp : Defines the entry point for the application.
//
#include "Problem1.h"

#include <iostream>

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++)
	{
		int N;
		int M;
		std::cin >> N;
		std::cin >> M;
		std::cout << Problem1::Solve(N) << std::endl;
	}

	return 0;
}
