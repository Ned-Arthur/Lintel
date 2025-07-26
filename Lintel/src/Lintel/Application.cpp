#include "Application.h"

#include "Random.h"

namespace Lintel {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		Lintel::Random::initialise();

		Setup();
		while (true)
		{
			Update();
		}
	}
}
