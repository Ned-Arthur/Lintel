#include "lnpch.h"
#include "Random.h"

namespace Lintel {
	void Random::Initialise()
	{
		srand(time(0));
	}

	int32_t Random::IntRange(int32_t lowerBound, int32_t upperBound)
	{
		int32_t range = upperBound - lowerBound + 1;
		int32_t randomNumber = rand() % range;
		return lowerBound + randomNumber;
	}
}
