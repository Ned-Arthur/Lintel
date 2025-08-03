#pragma once

#include <vector>

namespace Lintel {

	class Random
	{
	public:
		static void initialise();

		// Generate a random integer between lower and upper, inclusive
		static int intRange(int lower, int upper);

		// Pick a random item from a vector
		template <typename T>
		inline static T pickItem(std::vector<T> vec);
	};

	// Because this method uses a template it must be implemented in the header?
	// Maybe because it's then included in the app source and compiled when the usages are known...
	template<typename T>
	inline T Random::pickItem(std::vector<T> vec)
	{
		// We can't call rand() directly because this definition is included BEFORE
		// we call srand(time(0)). If we called rand() itself we'd get predictable
		// results each time the program runs
		int i = intRange(0, vec.size()-1);

		return vec.at(i);
	}

}
