#include <Lintel.h>

#include <windows.h>
#include <string>
#include <vector>
#include <ctime>

#define FOREGROUND_WHITE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED

CHAR_INFO makeChar_Win(char c, WORD attribs)
{
	CHAR_INFO chi;
	chi.Char.UnicodeChar = c;
	chi.Attributes = attribs;

	return chi;
}



class Sandbox : public Lintel::Application
{
public:
	Lintel::TRen ren;
	int x = 0;
	int y = 0;
	int w, h;

	void Setup() override
	{
		Lintel::TRen::getConsoleSize(&w, &h);
		ren.setTitle("Sandbox Game");
	}

	void Update() override
	{
		//Lintel::TRen::getConsoleSize(&w, &h);
		//ren.resize(w, h);
		//*
		Lintel::TChar flushChar('a', WHITE, RED);
		ren.flushBuffer(flushChar);
		Lintel::TChar cross('X', BLACK, CYAN);
		ren.drawChar(cross, x, y);
		x++; x %= w;
		y++; y %= h;
		ren.redraw();
		Sleep(50);
		//*/
	}
};

Lintel::Application* Lintel::CreateApplication()
{
	return new Sandbox();
}
