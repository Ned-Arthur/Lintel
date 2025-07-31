#include "Application.h"

#include <chrono>

#include "Random.h"
#include "LnTime.h"

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
			Lintel::Time::Update();
			Update();
		}
	}
	void Application::Quit()
	{
		isRunning = false;	// Drawing a sprite manually makes this not work :'(
		exit(0);			// Really really quit
	}
}
