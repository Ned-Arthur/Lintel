#include "LnTime.h"

namespace Lintel {

	float Time::deltaTime = 0;
	float Time::clockTime = 0;
	std::chrono::steady_clock::time_point Time::startTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point Time::lastTime = std::chrono::steady_clock::now();


	void Time::Update()
	{
		//static auto lastTime = std::chrono::steady_clock::now();
		auto currentTime = std::chrono::steady_clock::now();

		deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;

		clockTime = std::chrono::duration<float>(currentTime - startTime).count();
	}
}
