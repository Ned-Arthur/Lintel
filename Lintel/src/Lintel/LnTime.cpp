#include "lnpch.h"
#include "LnTime.h"

namespace Lintel {

	// Initialise static members
	float Time::DeltaTime = 0;
	float Time::ClockTime = 0;
	std::chrono::steady_clock::time_point Time::m_ClockStartTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point Time::m_LastFrameTime = std::chrono::steady_clock::now();

	void Time::Update()
	{
		auto currentTime = std::chrono::steady_clock::now();

		// Calculate DeltaTime
		DeltaTime = std::chrono::duration<float>(currentTime - m_LastFrameTime).count();
		m_LastFrameTime = currentTime;

		// Update ClockTime
		ClockTime = std::chrono::duration<float>(currentTime - m_ClockStartTime).count();
	}
}
