#pragma once

#include "Core.h"

namespace Lintel {

	class LINTEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Quit();
		double getDeltaTime();

		virtual void Setup() = 0;
		virtual void Update() = 0;

	private:
		bool isRunning;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
