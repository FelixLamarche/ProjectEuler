﻿// ProjectEuler.cpp : Defines the entry point for the application.
//
#include "Problem4.h"

#include <iostream>

int main()
{
	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++)
	{
		int N;
		std::cin >> N;
		std::cout << Problem4::Solve(N) << std::endl;
	}

	return 0;
}
