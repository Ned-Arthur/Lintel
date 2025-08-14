#include "Application.h"

#include <chrono>

#include "Random.h"
#include "LnTime.h"
#include "Input.h"

namespace Lintel {
	Application::Application()
		: isRunning(true)
	{}

	Application::~Application()
	{}

	void Application::Run()
	{
		Random::initialise();

		while (isRunning)
		{
			Time::Update();
			Input::Update();

			if (termRenderer)
			{
				termRenderer->GatherInput();
				if (termRenderer->wantsToQuit) Quit();
				termRenderer->UpdateAndDraw();
			}
			
		}
	}

	void Application::Quit()
	{
		// At one point this wouldn't work, but it's fine now...
		isRunning = false;
	}

	void Application::registerTRen(TRen* _termRenderer)
	{
		termRenderer = _termRenderer;
		termRenderer->setupThings();
	}
}
