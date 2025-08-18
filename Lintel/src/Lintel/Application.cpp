#include "Application.h"

#include <chrono>

#include "Random.h"
#include "LnTime.h"
#include "Input.h"

namespace Lintel {
	void Application::Run()
	{
		Random::initialise();

		while (m_Running)
		{
			Time::Update();
			Input::Update();

			if (m_TerminalRenderer)
			{
				m_TerminalRenderer->GatherInput();
				if (m_TerminalRenderer->wantsToQuit) Quit();
				m_TerminalRenderer->UpdateAndDraw();
			}
		}
	}

	void Application::Quit()
	{
		m_Running = false;
	}

	void Application::RegisterTRen(TRen* newTerminalRenderer)
	{
		m_TerminalRenderer = newTerminalRenderer;
		m_TerminalRenderer->setupThings();
	}
}
