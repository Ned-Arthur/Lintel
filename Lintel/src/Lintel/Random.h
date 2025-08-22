#pragma once

#include "Application.h"

#include "lnpch.h"

namespace Lintel {

	// Using a single API to the C rand functionality allows:
	// a) templates to use seeded random
	// b) One location if a swap to the C++ random functionality is preferred in future

	class Random
	{
	public:
		// Generate a random integer between lower and upper, inclusive
		static int32_t IntRange(int32_t lowerBound, int32_t upperBound);

		// Pick a random item from a vector
		template <typename T>
		inline static T PickItem(std::vector<T> vec);

	private:
		static void Initialise();

		friend void Application::Run();
	};

	template<typename T>
	inline T Random::PickItem(std::vector<T> vec)
	{
		int32_t randomIndex = IntRange(0, vec.size()-1);

		return vec.at(randomIndex);
	}
}
