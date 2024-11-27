#include "Problem13.h"

#include <numeric>

long long Problem13::Solve(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end)
{
	constexpr int nbDigitsInSolution = 10;

	const long long size = end - begin;
	int lengthDigitsInSum = nbDigitsInSolution + static_cast<int>(ceil(log10(static_cast<double>(size))));

	long long sum = 0;
	for (; begin != end; begin++)
	{
		sum += std::stoll((*begin).substr(0, lengthDigitsInSum));;
	}
	return std::stoll(std::to_string(sum).substr(0, nbDigitsInSolution));
}