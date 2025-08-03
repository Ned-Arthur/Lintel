#pragma once

namespace Lintel {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Quit();

		virtual void Setup() = 0;
		virtual void Update() = 0;

	private:
		bool isRunning;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
