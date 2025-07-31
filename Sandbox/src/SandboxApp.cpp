#include <Lintel.h>

class Sandbox : public Lintel::Application
{
public:
	Lintel::TRen ren;
	float x = 0;
	float y = 0;
	int w, h;
	char posString[30];

	double maxFps = 0.0;

	Lintel::TSprite sprite;

	void Setup() override
	{		
		sprite.setSpriteFromString("\\O/ | / \\", 3, 3, Lintel::I_MAGENTA, Lintel::I_WHITE);
		
		Lintel::TRen::getConsoleSize(&w, &h);

		ren.setTitle("Sandbox Game");
		ren.useConsole(&h, 1);
	}

	void Update() override
	{
		ren.update(&w, &h);
		
		
		
		double fps = 1 / Lintel::Time::deltaTime;
		if (Lintel::Time::clockTime > 1.0 && fps > maxFps) maxFps = fps;
		
		if (Lintel::Input::getKeyState(Lintel::K_ESCAPE).currentState) Quit();
		
		Lintel::TChar flushChar(' ', Lintel::WHITE, Lintel::WHITE);
		ren.flushBuffer(flushChar);

		

		ren.drawSprite(sprite, x - 1, y - 1);

		Lintel::TChar cross('X', Lintel::BLACK, Lintel::WHITE);
		//ren.drawChar(cross, x, y);
		float speed = 20.0f;
		if (Lintel::Input::getKeyState('A').currentState)
		{
			x -= (speed * Lintel::Time::deltaTime);
			ren.logString("Testing testing 123.");
		}
		if (Lintel::Input::getKeyState('D').currentState)
		{
			x += (speed * Lintel::Time::deltaTime);
			ren.logString("Another test...");
		}
		if (Lintel::Input::getKeyState('W').currentState)
		{
			y -= (speed * Lintel::Time::deltaTime);
		}
		if (Lintel::Input::getKeyState('S').currentState)
		{
			y += (speed * Lintel::Time::deltaTime);
		}
		if (x > w) x -= w;
		if (y > h) y -= h;
		if (x < 0) x += w;
		if (y < 0) y += h;

		sprintf(posString, "    FPS=%f", fps);
		ren.drawMsg(posString, Lintel::I_YELLOW, Lintel::GREEN, 10, 1);
		sprintf(posString, "Max FPS=%f", maxFps);
		ren.drawMsg(posString, Lintel::I_YELLOW, Lintel::GREEN, 10, 2);
		ren.drawChar(cross, w-1, h-1);

		
		
		ren.redraw();
	}
};

Lintel::Application* Lintel::CreateApplication()
{
	return new Sandbox();
}
