// Problem 43 Sub-string Divisibility
// We want the sum of all the 0 to 9 pandigital numbers (Numbers composed from each of those digits and only once)
// but also that they follow this property, where d1 is the first digit and d2 is the second digit, etc.
// With the 1st digit being the most significant digit
// d2d3d4 is divisible by 2
// d3d4d5 is divisible by 3
// d4d5d6 is divisible by 5
// d5d6d7 is divisible by 7
// d6d7d8 is divisible by 11
// d7d8d9 is divisible by 13
// d8d9d1 is divisible by 17


// Following that:
// d4 = 0,2,4,6,8
// d5 = 0,1,2,3,4,5,6,7,8,9
// d6 = 0, 5, but because d6d7d8 is divisible by 11, and d7!=d8, d6 cant be 0
// d6 = 5
// d7 = 0,1,2,3,4,5,6,7,8,9
// d8 = 0,1,2,3,4,5,6,7,8,9
// d9 = 0,1,2,3,4,5,6,7,8,9
// d10 = 0,1,2,3,4,5,6,7,8,9
// d6d7d8 = {506, 517, 528, 539, 561, 572, 583, 594}

// Possibilities:
// d1 = 0,1,2,3,4,6,7,8,9
// d2 = 0,1,2,3,4,6,7,8,9
// d3 = 0,1,2,3,4,6,7,8,9
// d4 = 0,2,4,6,8 
// d5 = 0,1,2,3,4,6,7,8,9
// d6 = 5
// d7 = 0,1,2,3,6,7,8,9
// d8 = 0,1,2,3,4,6,7,8,9
// d9 = 0,1,2,3,4,6,7,8,9
// d10 = 0,1,2,3,4,6,7,8,9

#include <iostream>

#define LOGF(str, ...) do { printf(str, __VA_ARGS__);} while(0)
using int64 = long long;

struct PandigitalFlag
{
	unsigned int digitsFlag = 0;
	int64 sum = 0;

	bool IsPandigital0To9() const
	{
		for (int digit = 0; digit < 10; ++digit)
		{
			if (!IsInFlag(digit))
				return false;
		}
		return true;
	}

	void AddToFlag(int digit)
	{
		digitsFlag = digitsFlag | (1 << digit);
		sum = (sum * 10) + digit;
	}
	void RemoveFromFlag(int digit)
	{
		digitsFlag = digitsFlag ^ (1 << digit);
		sum = sum / 10;
	}
	bool IsInFlag(int digit) const
	{
		return digitsFlag & (1 << digit);
	}
};

struct AddToPandigitalFlag
{
	PandigitalFlag& digitsFlag;
	int digit;
	AddToPandigitalFlag(PandigitalFlag& flag, int digit) : digitsFlag(flag), digit(digit)
	{
		flag.AddToFlag(digit);
	}
	~AddToPandigitalFlag()
	{
		digitsFlag.RemoveFromFlag(digit);
	}
};

static int64 Solve()
{
	const int digits1[] = { 0,1,2,3,4,6,7,8,9 };
	const int* digits2 = digits1;
	const int* digits3 = digits1;
	const int digits4[] = { 0,2,4,6,8 };
	const int* digits5 = digits1;
	const int digits6[] = { 5 };
	const int digits7[] = { 0,1,2,3,4,6,7,8,9 };
	const int* digits8 = digits1;
	const int* digits9 = digits1;
	const int* digits10 = digits1;

	const int digitsCounts[] = { 9, 9, 9, 5, 9, 1, 8, 9 ,9, 9 };

	// This should have been implemented as a recursive function or while keeping track individually of the digits
	int64 solutionSum = 0;
	PandigitalFlag digitsFlag;
	for (int i1 = 0; i1 < digitsCounts[0]; ++i1)
	{
		const int digit1 = digits1[i1];
		if (digitsFlag.IsInFlag(digit1))
			continue;
		AddToPandigitalFlag addDigit1(digitsFlag, digit1);

		for (int i2 = 0; i2 < digitsCounts[1]; ++i2)
		{
			const int digit2 = digits2[i2];
			if (digitsFlag.IsInFlag(digit2))
				continue;
			AddToPandigitalFlag addDigit2(digitsFlag, digit2);

			for (int i3 = 0; i3 < digitsCounts[2]; ++i3)
			{
				const int digit3 = digits3[i3];
				if (digitsFlag.IsInFlag(digit3))
					continue;
				AddToPandigitalFlag addDigit3(digitsFlag, digit3);

				for (int i4 = 0; i4 < digitsCounts[3]; ++i4)
				{
					const int digit4 = digits4[i4];
					if (digitsFlag.IsInFlag(digit4))
						continue;
					// d4 is divisible by 2
					AddToPandigitalFlag addDigit4(digitsFlag, digit4);

					for (int i5 = 0; i5 < digitsCounts[4]; ++i5)
					{
						const int digit5 = digits5[i5];
						if (digitsFlag.IsInFlag(digit5))
							continue;
						AddToPandigitalFlag addDigit5(digitsFlag, digit5);
						if ((digitsFlag.sum % 1000) % 3 != 0)
							continue;

						for (int i6 = 0; i6 < digitsCounts[5]; ++i6)
						{
							const int digit6 = digits6[i6];
							if (digitsFlag.IsInFlag(digit6))
								continue;
							AddToPandigitalFlag addDigit6(digitsFlag, digit6);
							if ((digitsFlag.sum % 1000) % 5 != 0)
								continue;

							for (int i7 = 0; i7 < digitsCounts[6]; ++i7)
							{
								const int digit7 = digits7[i7];
								if (digitsFlag.IsInFlag(digit7))
									continue;
								AddToPandigitalFlag addDigit7(digitsFlag, digit7);
								if ((digitsFlag.sum % 1000) % 7 != 0)
									continue;

								for (int i8 = 0; i8 < digitsCounts[7]; ++i8)
								{
									const int digit8 = digits8[i8];
									if (digitsFlag.IsInFlag(digit8))
										continue;
									AddToPandigitalFlag addDigit8(digitsFlag, digit8);
									if ((digitsFlag.sum % 1000) % 11 != 0)
										continue;

									for (int i9 = 0; i9 < digitsCounts[8]; ++i9)
									{
										const int digit9 = digits9[i9];
										if (digitsFlag.IsInFlag(digit9))
											continue;
										AddToPandigitalFlag addDigit9(digitsFlag, digit9);
										if ((digitsFlag.sum % 1000) % 13 != 0)
											continue;

										for (int i10 = 0; i10 < digitsCounts[9]; ++i10)
										{
											const int digit10 = digits10[i10];
											if (digitsFlag.IsInFlag(digit10))
												continue;
											AddToPandigitalFlag addDigit10(digitsFlag, digit10);
											if ((digitsFlag.sum % 1000) % 17 != 0)
												continue;

											if (digitsFlag.IsPandigital0To9())
											{
												LOGF("adding pandigital: %llu\n", digitsFlag.sum);
												solutionSum += digitsFlag.sum;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return solutionSum;
}

void main()
{
	const int64 solution = Solve();
	std::cout << "Problem 43 Solution: " << solution << std::endl;
}
