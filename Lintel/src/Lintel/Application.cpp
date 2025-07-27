#include "Application.h"

#include <chrono>

#include "Random.h"

namespace Lintel {
	Application::Application()
		: isRunning(true)
	{}

	Application::~Application()
	{}

	void Application::Run()
	{
		Lintel::Random::initialise();

		Setup();
		while (isRunning)
		{
			Update();
		}
	}
	void Application::Quit()
	{
		isRunning = false;
	}

	double Application::getDeltaTime()
	{
		static auto lastTime = std::chrono::steady_clock::now();
		auto currentTime = std::chrono::steady_clock::now();

		double deltaTime = std::chrono::duration<double>(currentTime - lastTime).count();
		lastTime = currentTime;

		return deltaTime;
	}
}
