#pragma once

#include "TermRender/TRen.h"

namespace Lintel {

	class Application
	{
	public:
		/* Operation Methods */
		void Run();
		void Quit();

		/* Renderer Methods */
		void RegisterTRen(TRen* newTerminalRenderer);

	private:
		bool m_Running = true;

		TRen* m_TerminalRenderer = nullptr;
	};
}
