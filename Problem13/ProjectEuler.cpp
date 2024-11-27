// ProjectEuler.cpp : Defines the entry point for the application.
//
#include "Problem13.h"

#include <iostream>
#include <string>

int main()
{
    int N;
    std::cin >> N;
    std::vector<std::string> strs;
    strs.reserve(N);
    for (int i = 0; i < N; ++i)
    {
        std::string s;
        std::cin >> s;
        strs.push_back(s);
    }

    std::cout << Problem13::Solve(strs.begin(), strs.end()) << std::endl;

	return 0;
}
