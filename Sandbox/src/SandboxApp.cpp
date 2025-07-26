#include <Lintel.h>

#include <windows.h>
#include <string>
#include <vector>
#include <ctime>

class Sandbox : public Lintel::Application
{
public:
	Lintel::TRen ren;
	int x = 0;
	int y = 0;
	int w, h;

	void Setup() override
	{
		//printf("\x1b[=0h");
		//printf("\x1b[38;5;41m");

		//*
		Lintel::TRen::getConsoleSize(&w, &h);
		ren.resize(w, h);
		ren.flushBuffer(' ');
		printf("%d,%d\n", w, h);
		for (int i = 0; i < h-1; i++)
		{
			printf("%d\n", i+1);
		}
		
		//*/
	}

	void Update() override
	{
		//Lintel::TRen::getConsoleSize(&w, &h);
		//ren.resize(w, h);
		/*
		ren.flushBuffer('.');
		ren.drawChar('X', x, y);
		x++;
		y++;
		if (x > w-10) x -= w+10;
		if (y > h-10) y -= h+10;
		ren.redraw();
		Sleep(500);
		//*/
	}
};

Lintel::Application* Lintel::CreateApplication()
{
	return new Sandbox();
}
