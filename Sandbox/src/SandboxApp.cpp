#include <Lintel.h>

#include <windows.h>
#include <string>
#include <vector>
#include <ctime>

#define FOREGROUND_WHITE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED

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
	}

	void Update() override
	{
		//Lintel::TRen::getConsoleSize(&w, &h);
		//ren.resize(w, h);
		//*
		CHAR_INFO flushChar;
		flushChar.Char.UnicodeChar = '.';
		flushChar.Attributes = FOREGROUND_WHITE | BACKGROUND_BLUE;
		ren.flushBuffer(flushChar);
		CHAR_INFO cross;
		cross.Char.UnicodeChar = 'X';
		cross.Attributes = BACKGROUND_BLUE;
		ren.drawChar(cross, x, y);
		x++; x %= w;
		y++; y %= h;
		ren.redraw();
		Sleep(500);
		//*/
	}
};

Lintel::Application* Lintel::CreateApplication()
{
	return new Sandbox();
}
