#pragma once

#include "Application.h"

#include "lnpch.h"

namespace Lintel {

	class Time
	{
	public:
		static float DeltaTime;		// Time since last frame
		static float ClockTime;		// Time since game start

	private:
		static void Update();		// Recalculate each member
		static std::chrono::steady_clock::time_point m_ClockStartTime;
		static std::chrono::steady_clock::time_point m_LastFrameTime;

		// Allow only this function to call Time::Update(), so the user can't mess with DeltaTime
		friend void Application::Run();
	};
}
