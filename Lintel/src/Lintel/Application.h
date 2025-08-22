#pragma once

#include "TermRender/TRen.h"

namespace Lintel {

	class Application
	{
	public:
		/* Operation Methods */
		void Run();

		/* Renderer Methods */
		void RegisterTRen(TRen* newTerminalRenderer);

	private:
		void Quit();
		bool m_Running = true;

		TRen* m_TerminalRenderer = nullptr;
	};
}
