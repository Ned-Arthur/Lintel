#pragma once

#include "Core.h"

#include <chrono>

namespace Lintel {

	class LINTEL_API Time
	{
	public:
		static float deltaTime;		// Time since last frame
		static float clockTime;		// Time since game start

		static void Update();		// Recalculate deltaTime

	private:
		static std::chrono::steady_clock::time_point startTime;
		static std::chrono::steady_clock::time_point lastTime;

		static float calculateDeltaTime();
	};

}
