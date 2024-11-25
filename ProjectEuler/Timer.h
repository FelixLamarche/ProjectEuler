#pragma once
#include <functional>

class Timer {
public:
	static double Time(std::function<void()> func);
	static void TimeAndOutput(std::function<void()> func);
};