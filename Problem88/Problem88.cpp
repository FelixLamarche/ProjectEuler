// Problem 88: Product-sum Numbers

#include <format>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <vector>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

static void GetFactorsDecreasingOrder(std::vector<u64>& factors, const u64 nb)
{
	// Exclude 1 for this as it is not needed
	for (u64 divider = nb; divider > 1; --divider)
	{
		if (nb % divider == 0)
			factors.push_back(divider);
	}
}

static void SolveIter(std::vector<u64>& minKs, const u64 targetNb, const std::vector<u64>& factors, const u64 nextFactorIdx, const u64 termsCount, const u64 curNbMultiplication, const u64 curNbAddition)
{
	if (curNbMultiplication > targetNb || curNbAddition > targetNb)
		return;
	if (curNbMultiplication == targetNb)
	{
		const u64 solutionTermsCount = termsCount + targetNb - curNbAddition; // Adds 1s to the addition to add up to the target
		if (solutionTermsCount < minKs.size())
		{
			const u64 prevMinNb = minKs[solutionTermsCount];
			minKs[solutionTermsCount] = std::min(prevMinNb, targetNb);
		}
		return;
	}

	for (u64 factorIdx = nextFactorIdx; factorIdx < factors.size(); ++factorIdx)
	{
		const u64 nextTerm = factors[factorIdx];
		SolveIter(minKs, targetNb, factors, factorIdx, termsCount + 1, nextTerm * curNbMultiplication, nextTerm + curNbAddition);
	}
}

static u64 Solve(const u64 upperBound)
{
	// a product-sum number can be written as 
	// N = a_1 * a_2 * ... * a_n = a_1 + a_2 + ... + a_n
	// 6 = 1 * 2 * 3 = 1 + 2 + 3
	// 8 = 1 * 1 * 2 * 4 = 1 + 1 + 2 + 4
	// for a given set of size k, there is a smallest N which fulfils this property
	// this function returns the sum of those minimal product-sum numbers between 2 <= k <= upperBound

	constexpr u64 defaultMinNumber = std::numeric_limits<u64>::max();

	std::vector<u64> minimalNumbersForSetSize(upperBound + 1, defaultMinNumber);
	minimalNumbersForSetSize[0] = 0;
	minimalNumbersForSetSize[1] = 0;
	u64 nextIdxValue = 2; // k=0, k=1 are both 0, and are already done

	u64 curNb = 2;
	std::vector<u64> factors;
	while (nextIdxValue < minimalNumbersForSetSize.size())
	{
		factors.clear();
		GetFactorsDecreasingOrder(factors, curNb);

		SolveIter(minimalNumbersForSetSize, curNb, factors, 0, 0, 1, 0);

		while (nextIdxValue < minimalNumbersForSetSize.size() && minimalNumbersForSetSize[nextIdxValue] != defaultMinNumber)
			++nextIdxValue;

		++curNb;
	}

	// skip the sets of size 0 and 1:
	const std::set<u64> setOfMinSumProductNumbers(minimalNumbersForSetSize.begin() + 2, minimalNumbersForSetSize.end());

	return std::accumulate(setOfMinSumProductNumbers.begin(), setOfMinSumProductNumbers.end(), 0ULL);
}

int main()
{
	const u64 kUpperBound = 12000;
	const u64 sol = Solve(kUpperBound);
	std::cout << "Solution 88: " << sol << std::endl;

	return 0;
}
