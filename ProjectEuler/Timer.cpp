#include "Timer.h"

#include <chrono>
#include <iostream>

double Timer::Time(std::function<void()> func)
{
	auto before = std::chrono::high_resolution_clock::now();
    func();
	auto after = std::chrono::high_resolution_clock::now();

	return (after - before).count() / 1000000000.0;
}

void Timer::TimeAndOutput(std::function<void()> func)
{
	double time = Timer::Time(func);
	std::cout << "Time taken: " << time << std::endl;
}
