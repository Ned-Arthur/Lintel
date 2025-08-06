#include "TRen.h"

#include "Input.h"

#include <cstdio>

#include <iostream>

// Platform specific implementations are better suited to the source I think;
// none of this is needed by users

// Colour translation tables
#ifdef LN_PLATFORM_WINDOWS
constexpr int TCTransFG_Win[16] = {
	0,
	FOREGROUND_RED,
	FOREGROUND_GREEN,
	FOREGROUND_BLUE,
	FOREGROUND_RED | FOREGROUND_GREEN,
	FOREGROUND_RED | FOREGROUND_BLUE,
	FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

	FOREGROUND_INTENSITY,
	FOREGROUND_INTENSITY | FOREGROUND_RED,
	FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};
constexpr int TCTransBG_Win[16] = {
	0,
	BACKGROUND_RED,
	BACKGROUND_GREEN,
	BACKGROUND_BLUE,
	BACKGROUND_RED | BACKGROUND_GREEN,
	BACKGROUND_RED | BACKGROUND_BLUE,
	BACKGROUND_GREEN | BACKGROUND_BLUE,
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,

	BACKGROUND_INTENSITY,
	BACKGROUND_INTENSITY | BACKGROUND_RED,
	BACKGROUND_INTENSITY | BACKGROUND_GREEN,
	BACKGROUND_INTENSITY | BACKGROUND_BLUE,
	BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
	BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
	BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
};



#endif

namespace Lintel {
#ifdef LN_PLATFORM_WINDOWS
	CHAR_INFO TChar::Translate_Win()
	{
		CHAR_INFO ret;
		ret.Char.AsciiChar = c;
		ret.Attributes = TCTransFG_Win[fg_col] | TCTransBG_Win[bg_col];
		return ret;
	}
#endif

	TRen::TRen()
	{
	#ifdef LN_PLATFORM_WINDOWS
		getConsoleSize(&width, &height);

		screenBuffer = new CHAR_INFO[width * height];

		wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
		rHnd = GetStdHandle(STD_INPUT_HANDLE);

		coordBufCoord.X = 0;
		coordBufCoord.Y = 0;

		coordBufSize.Y = height;
		coordBufSize.X = width;

		srctWriteRect.Top = 0;
		srctWriteRect.Left = 0;
		srctWriteRect.Bottom = height;
		srctWriteRect.Right = width;

		
		GetConsoleCursorInfo(wHnd, &oldCI);
		CONSOLE_CURSOR_INFO ci = oldCI;
		ci.bVisible = FALSE;
		SetConsoleCursorInfo(wHnd, &ci);

	#endif
	}
	TRen::~TRen()
	{
		// Free all the memory for our TThing s
		for (auto const& i : things)
		{
			delete i;
		}
		things.clear();

	#ifdef LN_PLATFORM_WINDOWS
		delete[] screenBuffer;
		
		//TODO tidy up the console
		SetConsoleCursorInfo(wHnd, &oldCI);
	#endif
	}

	void TRen::setupThings()
	{
		for (auto const& thing : things)
		{
			thing->genericSetup();
		}

		for (auto const& thing : things)
		{
			thing->LateSetup();
		}
	}

	TThing* TRen::getThingByName(std::string name)
	{
		for (auto const& thing : things)
		{
			if (thing->name == name)
			{
				return thing;
			}
		}
		return nullptr;
	}

	int TRen::getWidth() { return width; }
	int TRen::getHeight() { return height; }

	void TRen::getConsoleSize(int* columns, int* rows)
	{
	#ifdef LN_PLATFORM_WINDOWS
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		*columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		*rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	#endif
	}

	void TRen::setTitle(const char* termTitle)
	{
	#ifdef LN_PLATFORM_WINDOWS
		// Be naughty and use the ANSI function so we don't need to do a conversion
		SetConsoleTitleA(termTitle);
	#endif
	}

	// Call this every frame to check window events I guess
	void TRen::update()
	{
		// Handle (console) window events
		DWORD numEvents = 0;
		DWORD numEventsRead = 0;
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0)
		{
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

			for (DWORD i = 0; i < numEventsRead; ++i)
			{
				switch (eventBuffer[i].EventType)
				{
				case KEY_EVENT:
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_ESCAPE:
						Input::setKeyState(K_ESCAPE, true);
						
						break;
					}

					Input::setKeyState(eventBuffer[i].Event.KeyEvent.uChar.AsciiChar, eventBuffer[i].Event.KeyEvent.bKeyDown);

					break;
				case WINDOW_BUFFER_SIZE_EVENT:
					COORD newSize = eventBuffer[i].Event.WindowBufferSizeEvent.dwSize;
					// Update all our variables to store & draw at the right sizes
					resize(newSize.X, newSize.Y);
				}
			}

			delete[] eventBuffer;
		}
	}

	void TRen::resize(int w, int h)
	{
		width = w;
		height = h;

	#ifdef LN_PLATFORM_WINDOWS
		delete screenBuffer;
		screenBuffer = new CHAR_INFO[width * height];

		coordBufSize.Y = height;
		coordBufSize.X = width;

		srctWriteRect.Bottom = height;
		srctWriteRect.Right = width;
	#endif
	}

	void TRen::redraw()
	{
		// Update all our TThings
		for (auto const& i : things)
		{
			i->Update();
			i->Draw();
		}
		
		// Draw the character buffer to the console
	#ifdef LN_PLATFORM_WINDOWS
		// Use ANSI method so we don't have to deal with conversion bs and can
		// just use ASCII/ANSI chars in App and maintain cross-platform-ness
		WriteConsoleOutputA(
			wHnd,
			screenBuffer,
			coordBufSize,
			coordBufCoord,
			&srctWriteRect);
	#endif
	}

	// Drawing methods
	void TRen::flushBuffer(TChar blankChar)
	{
		// In theory we just translate our TChar to the platform-appropriate type
		// and call it `c` in the ifdef block. We'll see if this pans out when
		// adding more platforms
	#ifdef LN_PLATFORM_WINDOWS
		CHAR_INFO c = blankChar.Translate_Win();
	#endif
		
		for (int i = 0; i < width * height; i++)
		{
			screenBuffer[i] = c;
		}
	}

	void TRen::drawMsg(const char* msg, TChar temp, int x, int y)
	{
		for (int i = 0; i < strlen(msg); i++)
		{
			temp.c = msg[i];
			drawChar(temp, x + i, y);
		}
	}
	void TRen::drawMsg(const char* msg, TermColour fgColour, TermColour bgColour, int x, int y)
	{
		for (int i = 0; i < strlen(msg); i++)
		{
			drawChar(TChar(msg[i], fgColour, bgColour), x + i, y);
		}
	}

	void TRen::drawSprite(TSprite sprite, int x, int y)
	{
		// Check the bounds first so we can avoid bounds-checking every char
		int w = sprite.getWidth();
		int h = sprite.getHeight();

		int wStart = 0;
		int hStart = 0;

		// Pre-check all of our bounds so we can drawUnsafe
		if (x < 0)
			wStart -= x;
		if (y < 0)
			hStart -= y;
		if (x + w > width)
			w -= (x + w) - width;
		if (y + h > height)
			h -= (y + h) - height;
		
		for (int i = wStart; i < w; i++)
		{
			for (int j = hStart; j < h; j++)
			{
				drawCharUnsafe(sprite.getCharAtPosition(i, j), x + i, y + j);
			}
		}
	}

	void TRen::drawChar(TChar sourceChar, int x, int y)
	{
		if (x >= width || y >= height || x < 0 || y < 0)
		{
			//exit(99);	// If we're trying to 'optimise' drawing we can crash on using this
			return;
		}

		drawCharUnsafe(sourceChar, x, y);
	}
	void TRen::drawCharUnsafe(TChar sourceChar, int x, int y)
	{
#ifdef LN_PLATFORM_WINDOWS
		CHAR_INFO c = sourceChar.Translate_Win();
#endif

		screenBuffer[y * width + x] = c;
	}
}
