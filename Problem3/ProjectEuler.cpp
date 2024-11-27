// ProjectEuler.cpp : Defines the entry point for the application.
//
#include "Problem3.h"

#include <iostream>

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++)
	{
		long long N;
		std::cin >> N;
		std::cout << Problem3::Solve(N) << std::endl;
	}

	return 0;
}
