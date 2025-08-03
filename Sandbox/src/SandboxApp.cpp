#include <Lintel.h>

class Sandbox : public Lintel::Application
{
public:
	Lintel::TRen ren;
	float x = 10;
	float y = 10;
	float speed = 10.0f;
	int w, h;
	static const size_t pStrSize = 30;
	char posString[pStrSize];

	Lintel::TSprite sprite;

	void Setup() override
	{		
		//sprite.setSpriteFromString("\\O/ | / \\", 3, 3, Lintel::I_MAGENTA, Lintel::I_WHITE);
		sprite.loadSprite("assets/demo.spt");

		Lintel::TRen::getConsoleSize(&w, &h);

		ren.setTitle("Sandbox Game");
	}

	void Update() override
	{
		ren.update(&w, &h);
		
		if (Lintel::Input::getKeyState(Lintel::K_ESCAPE).currentState) Quit();
		
		Lintel::TChar flushChar(' ', Lintel::WHITE, Lintel::WHITE);
		ren.flushBuffer(flushChar);

		ren.drawSprite(sprite, (int)(x - 1), (int)(y - 1));

		Lintel::TChar cross('X', Lintel::BLACK, Lintel::WHITE);

		sprintf_s(posString, pStrSize, "%f, %f", x, y);
		ren.drawMsg(posString, Lintel::I_YELLOW, Lintel::GREEN, w-30, 1);
		sprintf_s(posString, pStrSize, "%d, %d", (int)x, (int)y);
		ren.drawMsg(posString, Lintel::I_YELLOW, Lintel::GREEN, w - 30, 2);

		ren.drawChar(cross, w-1, h-1);
		
		ren.redraw();

		if (Lintel::Input::getKeyState('A').currentState)
		{
			x -= (speed * Lintel::Time::deltaTime);
		}
		if (Lintel::Input::getKeyState('D').currentState)
		{
			x += (speed * Lintel::Time::deltaTime);
		}
		if (Lintel::Input::getKeyState('W').currentState)
		{
			y -= (speed * Lintel::Time::deltaTime);
		}
		if (Lintel::Input::getKeyState('S').currentState)
		{
			y += (speed * Lintel::Time::deltaTime);
		}
		if (x > w) x -= w+1;
		if (y > h) y -= h+1;
		if (x < -1) x += w+1;
		if (y < -1) y += h+1;
	}
};

Lintel::Application* Lintel::CreateApplication()
{
	return new Sandbox();
}
