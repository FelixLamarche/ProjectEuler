#pragma once

#include <vector>

namespace Utils {
class Sieve {
	public:
		Sieve(int size)
			: _sieve(size, true)
		{
			InitSieve();
		}

		bool IsPrime(int nb) const
		{
			return _sieve[nb];
		}

		size_t Size() const
		{
			return _sieve.size();
		}

private:
	std::vector<bool> _sieve;

	void InitSieve();
};
}