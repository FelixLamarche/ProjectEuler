// ProjectEuler.cpp : Defines the entry point for the application.
//
#include "Problem9.h"

#include <iostream>
#include <string>

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++)
	{
		int N;
		std::cin >> N;
		std::cout << Problem9::Solve(N) << std::endl;
	}

	return 0;
}
