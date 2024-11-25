#pragma once

#include <chrono>
#include <iostream>
#include <numeric>
#include <string>

class TimerBlock {
public:
	TimerBlock(const std::string& name)
		: _name(name), _start(std::chrono::high_resolution_clock::now())
	{ }
		
	~TimerBlock()
	{
		const auto end = std::chrono::high_resolution_clock::now();
		const auto duration = (end - _start).count();
		const auto seconds = duration / 1'000'000'000;
		
		const std::string nsStr = std::to_string(duration % 1'000'000'000);
		constexpr size_t nbDigits = 8;
		auto new_str = std::string(nbDigits - std::min(nbDigits, nsStr.length()), '0') + nsStr;
		std::cout << _name << ": " << seconds << "." << new_str << " secs." << std::endl;
	}
private:
	std::string _name;
	std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};