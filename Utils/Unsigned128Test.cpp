#include "Unsigned128.h"

#include <format>
#include <iostream>
#include <limits>

#define LOG(str) do { std::cout << str << std::endl; } while(0)
#define LOGF(str, ...) do { printf(str, __VA_ARGS__); } while(0)
#define LOGFMT(str, ...) do { std::cout << std::format(str, __VA_ARGS__);} while(0)

using uint32 = unsigned long;
using uint64 = unsigned long long;

static bool EqualityTest()
{
	constexpr uint32 upperLimit = 10'000;
	for (uint32 i = 0; i < upperLimit; ++i)
	{
		if (uint128(i) != i)
			return false;
	}

	constexpr uint64 bigConstant = UINT64_MAX;
	constexpr uint128 bigNb = bigConstant;
	if(bigNb != bigConstant)
		return false;

	return true;
}

static bool PostFixAdditionTest()
{
	constexpr uint32 upperLimit = 10'000;
	uint128 nb = 0;
	for (uint32 i = 0; i < upperLimit; ++i)
	{
		if (nb++ != i)
			return false;
	}
	return true;
}

static bool PreFixAdditionTest()
{
	constexpr uint32 upperLimit = 10'000;
	uint128 nb = 0;
	for (uint32 i = 0; i < upperLimit; ++i)
	{
		if (++nb != i + 1)
			return false;
	}
	return true;
}

static bool PostFixSubstractionTest()
{
	constexpr uint32 upperLimit = 10'000;
	uint128 nb = upperLimit;
	for (uint32 i = upperLimit; i > 0; --i)
	{
		if (nb-- != i)
			return false;
	}
	return true;
}

static bool PreFixSubstractionTest()
{
	constexpr uint32 upperLimit = 10'000;
	uint128 nb = upperLimit;
	for (uint32 i = upperLimit; i > 0; --i)
	{
		if (--nb != i - 1)
			return false;
	}
	return true;
}

static bool ToStringTest()
{
	constexpr uint32 upperLimit = 10'000;
	for (uint32 i = 0; i < upperLimit; ++i)
	{
		const uint128 nb = i;
		const std::string nbStr = nb.ToString();
		const std::string iStr = std::to_string(i);
		if (nbStr != iStr)
			return false;
	}

	constexpr uint64 big64 = UINT64_MAX;
	constexpr uint128 big128 = big64;
	const std::string big64Str = std::to_string(UINT64_MAX);
	const std::string big128Str = big128.ToString();

	if (big64Str != big128Str)
		return false;

	return true;
}

static bool AdditionTest()
{
	const uint64 a = 123'456'789'012'345;
	const uint64 b = 987'654'321'987'654;

	const uint128 a128 = a;
	const uint128 b128 = b;

	const uint64 sum64 = a + b;
	const uint128 sum128 = a128 + b128;

	if (sum64 != sum128)
		return false;

	return true;
}

static bool SubstractionTest()
{
	const uint64 a = 123'456'789'012'345;
	const uint64 b = 987'654'321'987'654;

	const uint128 a128 = a;
	const uint128 b128 = b;

	const uint64 diff64 = b - a;
	const uint128 diff128 = b128 - a128;

	if (diff64 != diff128)
		return false;

	return true;
}

static bool MultiplicationTest()
{
	const uint64 a = 123'456'789;
	const uint64 b = 987'654'321;

	const uint64 prod64 = a * b;

	const uint128 a128 = a;
	const uint128 b128 = b;
	const uint128 prod128 = a128 * b128;

	if (prod64 != prod128)
		return false;

	return true;
}

static bool DivisionTest()
{
	const uint64 a = 11;
	const uint64 b = UINT64_MAX;
	const uint64 div64 = b / a;

	const uint128 a128 = a;
	const uint128 b128 = b;
	const uint128 div128 = b128 / a128;

	if (div64 != div128)
		return false;

	uint64 nb64 = UINT64_MAX;
	uint128 nb128 = nb64;

	while (nb64 > 0)
	{
		nb64 /= 10;
		nb128 /= 10;
		if (nb64 != nb128)
			return false;
	}

	return true;
}

void main()
{
	const bool equalityTest = EqualityTest();
	if (!equalityTest)
		LOGF("Equality test failed.\n");

	const bool postFixAdditionTest = PostFixAdditionTest();
	if (!postFixAdditionTest)
		LOGF("PostFixAdditionTest failed.\n");

	const bool preFixAdditionTest = PreFixAdditionTest();
	if (!preFixAdditionTest)
		LOGF("PreFixAdditionTest failed.\n");

	const bool postFixSubstractionTest = PostFixSubstractionTest();
	if (!postFixSubstractionTest)
		LOGF("PostFixSubstractionTest failed.\n");

	const bool preFixSubstractionTest = PreFixSubstractionTest();
	if (!preFixSubstractionTest)
		LOGF("PreFixSubstractionTest failed.\n");

	const bool toStringTest = ToStringTest();
	if (!toStringTest)
		LOGF("ToStringTest failed.\n");

	const bool additionTest = AdditionTest();
	if (!additionTest)
		LOG("AdditionTest failed.\n");

	const bool substractionTest = SubstractionTest();
	if (!substractionTest)
		LOG("SubstractionTest failed.\n");

	const bool multTest = MultiplicationTest();
	if (!multTest)
		LOG("MultiplicationTest failed.\n");

	const bool divTest = DivisionTest();
	if (!divTest)
		LOG("DivisionTest failed.\n");
}


