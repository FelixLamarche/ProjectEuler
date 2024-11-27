// ProjectEuler.cpp : Defines the entry point for the application.
//
#include "Problem8.h"

#include <iostream>
#include <string>

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++)
	{
		int N;
		int K;
		std::cin >> N;
		std::cin >> K;
		std::string nb;
		nb.reserve(N);
		std::cin >> nb;
		std::cout << Problem8::Solve(nb, K) << std::endl;
	}

	return 0;
}
