#include "lnpch.h"
#include "Application.h"

#include "Random.h"
#include "LnTime.h"
#include "Input.h"

namespace Lintel {
	void Application::Run()
	{
		Random::Initialise();

		while (m_Running)
		{
			Time::Update();
			Input::Update();

			if (m_TerminalRenderer)
			{
				m_TerminalRenderer->GatherInput();
				if (m_TerminalRenderer->WantsToQuit) Quit();
				m_TerminalRenderer->UpdateAndDraw();
			}
		}
	}

	void Application::RegisterTRen(TRen* newTerminalRenderer)
	{
		m_TerminalRenderer = newTerminalRenderer;
		m_TerminalRenderer->SetupThings();
	}

	void Application::Quit()
	{
		m_Running = false;
	}
}
