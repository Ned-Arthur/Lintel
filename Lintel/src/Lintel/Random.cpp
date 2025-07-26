#include "Random.h"

#include <cstdlib>
#include <ctime>

namespace Lintel {
	void Random::initialise()
	{
		srand(time(0));
	}

	int Random::intRange(int lower, int upper)
	{
		int range = upper - lower;
		int r = rand() % (range + 1);
		return r + lower;
	}
}
