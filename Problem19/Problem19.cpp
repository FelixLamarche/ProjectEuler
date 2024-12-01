// Problem: 19. Counting Sundays
// How many Sundays fell on the first of the month between two dates

#include <functional>
#include <iostream>

static int Solve(long long Y1, int M1, int D1, long long Y2, int M2, int D2)
{
	constexpr int daysInYear = 365;
	constexpr int daysInMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	constexpr int daysInWeek = 7;
	constexpr int monthsInYear = 12;
	
	const std::function<bool(long long)> isLeapYear = [](long long y) { return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0); };

	// 1900-01-01 is a Monday
	int day = 1;
	int month = 1;
	long long year = 1900;
	// 0 is sunday, 1 is monday, ..., 6 is saturday
	int dayOfWeek = 1; // Monday

	long long daysSince1900 = (Y1 - year) * daysInYear;
	// Add leap years (occurs on years dividable by 4, but not by 100, unless it is dividable by 400)
	// We do year - 1, because we must finish the year to count the leap day
	daysSince1900 += (Y1 - year - 1) / 4;
	if (Y1 >= 2000)                                                                                                                                              
	{
		// We have counted all the days from 1900 to 2000,
		// but we need to start the weird leap year calculation from 2000 in the 400-year cycle
		year = 2000;
		daysSince1900 -= (Y1 - year - 1) / 100;
		daysSince1900 += (Y1 - year - 1) / 400;
	}
	year = Y1;

	while (month < M1)
	{
		daysSince1900 += daysInMonth[month];
		if (month == 2 && isLeapYear(year))
		{
			daysSince1900++;
		}
		month++;
	}
	daysSince1900 = daysSince1900 + D1 - 1;
	day = D1;

	// Calculate the day of the week of the first date
	dayOfWeek = (dayOfWeek + daysSince1900) % daysInWeek;

	// Count the sundays on the first of each month
	int nbSundaysOnFirst = 0;

	// Get the day to be the first of the month
	if(day == 1)
	{
		if (dayOfWeek == 0)
		{
			nbSundaysOnFirst++;
		}
	}
	else // Add the days of the current month and go to the next one
	{
		dayOfWeek = (dayOfWeek + daysInMonth[month] - day + 1) % daysInWeek;
		if (isLeapYear(year) && month == 2)
		{
			dayOfWeek = (dayOfWeek + 1) % daysInWeek;
		}
		day = 1;
		month = (month + 1) % (monthsInYear + 1);
		month = month == 0 ? 1 : month;
		year = month == 1 ? year + 1 : year;
		if (dayOfWeek == 0)
		{
			nbSundaysOnFirst++;
		}
	}

	for (; year < Y2; year++)
	{
		const bool isLeap = isLeapYear(year);
		for (; month <= monthsInYear; month++)
		{
			dayOfWeek = (dayOfWeek + daysInMonth[month]) % daysInWeek;
			if (month == 2 && isLeap)
			{
				dayOfWeek = (dayOfWeek + 1) % daysInWeek;
			}

			// We have a sunday on the first of the month
			if (dayOfWeek == 0)
			{
				nbSundaysOnFirst++;
			}
		}
		month = 1;
	}
	
	while (month < M2)
	{
		dayOfWeek = (dayOfWeek + daysInMonth[month]) % daysInWeek;
		if (month == 2 && isLeapYear(year))
		{
			dayOfWeek = (dayOfWeek + 1) % daysInWeek;
		}
		// We have a sunday on the first of the month
		if (dayOfWeek == 0)
		{
			nbSundaysOnFirst++;
		}
		month++;
	}

	return nbSundaysOnFirst;
}


int main()
{
	int T;
	std::cin >> T;
	for (int i = 0; i < T; i++)
	{
		long long Y1;
		int M1;
		int D1;
		long long Y2;
		int M2;
		int D2;
		std::cin >> Y1 >> M1 >> D1 >> Y2 >> M2 >> D2;

		std::cout << Solve(Y1, M1, D1, Y2, M2, D2) << std::endl;
	}

	return 0;
}