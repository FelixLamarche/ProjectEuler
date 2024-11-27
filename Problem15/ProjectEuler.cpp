// ProjectEuler.cpp : Defines the entry point for the application.
//

#include "Problem15.h"

#include <iostream>
#include <string>

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
		std::cout << Problem15::Solve(N, M) << std::endl;
	}

	return 0;
}
