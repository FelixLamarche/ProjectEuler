// Problem 93: Arithmetic Expressions

#include <array>
#include <format>
#include <functional>
#include <iostream>
#include <set>

#define LOGF(lineStr, ...) do { printf(lineStr, __VA_ARGS__); } while(0)
#define LOGFMT(lineStr, ...) do { std::cout << std::format(lineStr, __VA_ARGS__); } while(0)

using u32 = unsigned long;
using u64 = unsigned long long;
using i32 = signed long;
using i64 = signed long long;

static int CalculateLongestNumberChain(const float a, const float b, const float c, const float d)
{
	constexpr float invalidOperationResult = -999.999f;

	using MathOperator = std::function<float(float, float)>;
	MathOperator addFunc = [](const float a, const float b) { return a + b; };
	MathOperator substractFunc = [](const float a, const float b) { return a - b; };
	MathOperator substractInvFunc = [](const float a, const float b) { return b - a; };
	MathOperator multiplyFunc = [](const float a, const float b) { return a * b; };
	MathOperator divideFunc = [invalidOperationResult](const float a, const float b) { return b == 0.f ? invalidOperationResult : a / b; };
	MathOperator divideInvFunc = [invalidOperationResult](const float a, const float b) { return a == 0.f ? invalidOperationResult : b / a; };

	const std::array<MathOperator, 6> mathOperators = { addFunc, substractFunc, multiplyFunc, divideFunc, substractInvFunc, divideInvFunc };
	const std::array<float, 4> operands = { a, b, c, d };

	std::set<int> nbs;
	for (int operand1Idx = 0; operand1Idx < operands.size(); ++operand1Idx)
	{
		const float operand1 = operands[operand1Idx];
		for (int operand2Idx = 0; operand2Idx < operands.size(); ++operand2Idx)
		{
			if (operand2Idx == operand1Idx)
				continue;
			const float operand2 = operands[operand2Idx];

			for (int operand3Idx = 0; operand3Idx < operands.size(); ++operand3Idx)
			{
				if (operand3Idx == operand2Idx || operand3Idx == operand1Idx)
					continue;
				const float operand3 = operands[operand3Idx];

				for (int operand4Idx = 0; operand4Idx < operands.size(); ++operand4Idx)
				{
					if (operand4Idx == operand3Idx || operand4Idx == operand2Idx || operand4Idx == operand1Idx)
						continue;
					const float operand4 = operands[operand4Idx];

					for (int operator1Idx = 0; operator1Idx < mathOperators.size(); ++operator1Idx)
					{
						const MathOperator& operator1 = mathOperators[operator1Idx];
						for (int operator2Idx = 0; operator2Idx < mathOperators.size(); ++operator2Idx)
						{
							const MathOperator& operator2 = mathOperators[operator2Idx];
							for (int operator3Idx = 0; operator3Idx < mathOperators.size(); ++operator3Idx)
							{
								const MathOperator& operator3 = mathOperators[operator3Idx];

								{
									bool isInvalidResult = false;
									float result = operator1(operand1, operand2);
									isInvalidResult = isInvalidResult || result == invalidOperationResult;
									result = operator2(result, operand3);
									isInvalidResult = isInvalidResult || result == invalidOperationResult;
									result = operator3(result, operand4);
									isInvalidResult = isInvalidResult || result == invalidOperationResult;

									// result is not an integer
									//if (!(result + 0.0001f > std::trunc(result) && result - 0.0001f < std::trunc(result)))
									if (result == std::trunc(result))
									{
										const int resultInt = result;
										if (resultInt >= 1)
											nbs.insert(resultInt);
									}
								}

								{
									bool isInvalidResult = false;
									float result = operator1(operand1, operand2);
									isInvalidResult = isInvalidResult || result == invalidOperationResult;
									float result2 = operator3(operand3, operand4);
									isInvalidResult = isInvalidResult || result2 == invalidOperationResult;
									result = operator3(result, result2);
									isInvalidResult = isInvalidResult || result == invalidOperationResult;

									// result is not an integer
									//if (!(result + 0.0001f > std::trunc(result) && result - 0.0001f < std::trunc(result)))
									if (result == std::trunc(result))
									{
										const int resultInt = result;
										if (resultInt >= 1)
											nbs.insert(resultInt);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// Try to get all nbs from 1..N then return when the chain breaks
	int nextNb = 1;
	while (nbs.contains(nextNb))
		nextNb++;

	return nextNb - 1;
}

static int Solve()
{
	int biggestNbChain = 0;
	int biggestNbChainDigits = 0;

	constexpr int biggestDigit = 9;
	for (int a = 1; a <= biggestDigit; ++a)
	{
		for (int b = a + 1; b <= biggestDigit; ++b)
		{
			for (int c = b + 1; c <= biggestDigit; ++c)
			{
				for (int d = c + 1; d <= biggestDigit; ++d)
				{
					const int numberChain = CalculateLongestNumberChain(a, b, c, d);
					if (numberChain > biggestNbChain)
					{
						biggestNbChain = numberChain;
						biggestNbChainDigits = a * 1000 + b * 100 + c * 10 + d;
						LOGFMT("New Best: {}: Chain: {}\n", biggestNbChainDigits, biggestNbChain);
					}
				}
			}
		}
	}

	return biggestNbChainDigits;
}

int main()
{
	const int sol = Solve();
	std::cout << "Solution 93: " << sol << std::endl;

	return 0;
}