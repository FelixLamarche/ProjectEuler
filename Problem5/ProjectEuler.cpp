// ProjectEuler.cpp : Defines the entry point for the application.
//
#include "Problem5.h"

#include <iostream>

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++)
	{
		int N;
		std::cin >> N;
		std::cout << Problem5::Solve(N) << std::endl;
	}

	return 0;
}
