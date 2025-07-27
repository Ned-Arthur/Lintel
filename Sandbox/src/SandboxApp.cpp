#include <Lintel.h>

#include <windows.h>

class Sandbox : public Lintel::Application
{
public:
	Lintel::TRen ren;
	float x = 0;
	float y = 0;
	int w, h;
	char posString[30];

	double maxFps = 0.0;
	double runningTime = 0.0;

	void Setup() override
	{
		Lintel::TRen::getConsoleSize(&w, &h);
		ren.setTitle("Sandbox Game");
	}

	void Update() override
	{
		double dT = getDeltaTime();
		runningTime += dT;
		double fps = 1 / dT;
		if (runningTime > 1.0 && fps > maxFps) maxFps = fps;
		
		Lintel::TRen::getConsoleSize(&w, &h);
		//ren.resize(w, h);
		ren.update();
		if (ren.escPressed == true) Quit();
		Lintel::TChar flushChar(' ', WHITE, WHITE);
		ren.flushBuffer(flushChar);

		Lintel::TChar cross('X', BLACK, WHITE);
		ren.drawChar(cross, x, y);
		float speed = 20.0f;
		if (GetAsyncKeyState('A'))
		{
			x -= (speed * dT);
		}
		if (GetAsyncKeyState('D'))
		{
			x += (speed * dT);
		}
		if (GetAsyncKeyState('W'))
		{
			y -= (speed * dT);
		}
		if (GetAsyncKeyState('S'))
		{
			y += (speed * dT);
		}
		if (x > w) x -= w;
		if (y > h) y -= h;
		if (x < 0) x += w;
		if (y < 0) y += h;

		sprintf(posString, "    FPS=%f", fps);
		ren.drawMsg(posString, I_YELLOW, GREEN, 10, 1);
		sprintf(posString, "Avg FPS=%f", maxFps);
		ren.drawMsg(posString, I_YELLOW, GREEN, 10, 2);
		ren.drawChar(cross, w-1, h-1);
		ren.redraw();
	}
};

Lintel::Application* Lintel::CreateApplication()
{
	return new Sandbox();
}
