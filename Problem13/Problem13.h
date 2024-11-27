#pragma once

#include <string>
#include <vector>


/// <summary>
/// Given a list of N numbers, find the first 10 digits of the sum of the numbers.
/// </summary>
class Problem13
{
public:
	static long long Solve(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end);
};