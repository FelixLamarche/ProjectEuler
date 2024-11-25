#include "Sieve.h"

void Utils::Sieve::InitSieve()
{
	// Sieve should already be set as all true

	if (_sieve.size() >= 2)
	{
		_sieve[1] = false;
		_sieve[0] = false;
	}
	else if (_sieve.size() == 1)
	{
		_sieve[0] = false;
	}
	else
	{
		return;
	}
	
	for (size_t i = 2; i < _sieve.size(); i++)
	{
		for (size_t j = 2; j * i < _sieve.size(); j++)
		{
			_sieve[j * i] = false;
		}
	}
}