#pragma once

#include "TermRender/TRen.h"

namespace Lintel {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		/* Operation Methods */
		void Run();
		void Quit();

		/* Renderer Methods */
		void registerTRen(TRen* _termRenderer);

	private:
		bool isRunning;

		TRen* termRenderer;
	};
}
