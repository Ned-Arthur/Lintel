#pragma once

#include "Core.h"

namespace Lintel {

	class LINTEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		virtual void Setup() = 0;
		virtual void Update() = 0;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
