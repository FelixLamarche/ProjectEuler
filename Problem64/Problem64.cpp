// Problem 64: Odd Period Square Roots

#include <assert.h>
#include <format>
#include <iostream>
#include <vector>

using u32 = unsigned long;
using u64 = unsigned long long;

#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(0)
#define LOGFMT(str, ...) do { std::cout << std::format(str, __VA_ARGS__); } while(0)

static u32 Solve(const u32 maxNb)
{
	u32 irrationalOddPeriodCount = 0;

	struct StepData
	{
		int a = 0;
		int divider = 0;
		int substracter = 0;

		bool operator==(const StepData& rhs)
		{
			return a == rhs.a && divider == rhs.divider && substracter == rhs.substracter;
		}
	};

	for (int n = 2; n <= maxNb; ++n)
	{
		const double nSqrRoot = sqrt(n);

		// If not an irrational nb
		if (nSqrRoot == ceil(nSqrRoot))
			continue;

		const int a0 = floor(nSqrRoot);

		StepData step;
		step.a = a0;
		step.substracter = a0;
		step.divider = 1;

		auto doStep = [n, a0](const StepData& stepData)
			{
				int numMultiplier = stepData.divider;
				int newDivider = n - stepData.substracter * stepData.substracter;
				assert(newDivider % numMultiplier == 0, "Does not always cancel out.");
				newDivider /= numMultiplier;

				// new fraction has to be in the range of ]0, 1[
				int diff = stepData.substracter + a0;
				int newA = diff / newDivider;
				int newSubstracter = abs(stepData.substracter - newA * newDivider);

				StepData newStepData;
				newStepData.a = newA;
				newStepData.substracter = newSubstracter;
				newStepData.divider = newDivider;
				return newStepData;
			};

		std::vector<StepData> steps;

		step = doStep(step);

		while (std::find(steps.begin(), steps.end(), step) == steps.end())
		{
			steps.push_back(step);
			step = doStep(step);
		}

		LOGFMT("Sqrt({})=[{},(", n, a0);
		for (const StepData& stepData : steps)
			LOGFMT("{},", stepData.a);
		LOGFMT(")], period = {}.\n", steps.size());

		if (steps.size() % 2 == 1)
			irrationalOddPeriodCount++;

	}

	return irrationalOddPeriodCount;
}

void main()
{
	constexpr u32 maxNb = 10000;
	const u32 sol = Solve(maxNb);
	std::cout << "Solution 64: " << sol << std::endl;
}
