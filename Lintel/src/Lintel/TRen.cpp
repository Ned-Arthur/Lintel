#include "TRen.h"

#include <cstdio>

// Platform specific implementations are better suited to the source I think;
// None of this is needed by users

#define ToWchar(from, to) MultiByteToWideChar(CP_ACP, 0, &from, 1, &to, 1)

// Translation tables
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
	CHAR_INFO TChar::Translate_Win()
	{
		CHAR_INFO ret;
		ToWchar(c, ret.Char.UnicodeChar);
		ret.Attributes = TCTransFG_Win[fg_col] | TCTransBG_Win[bg_col];
		return ret;
	}

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
	#endif
	}
	TRen::~TRen()
	{
	#ifdef LN_PLATFORM_WINDOWS
		delete screenBuffer;
	#endif
	}

	// Get the rows and columns of the console. This is platform-specific code
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

	void TRen::resize(int w, int h)
	{
		width = w;
		height = h;

		// Reallocate the character buffer
	#ifdef LN_PLATFORM_WINDOWS
		delete screenBuffer;
		screenBuffer = new CHAR_INFO[width * height];
	#endif
	}

	void TRen::redraw()
	{
	#ifdef LN_PLATFORM_WINDOWS
		WriteConsoleOutput(
			wHnd,
			screenBuffer,
			coordBufSize,
			coordBufCoord,
			&srctWriteRect);
	#endif
 	}

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

	void TRen::drawChar(TChar sourceChar, int x, int y)
	{
		if (x >= width || y >= height)
		{
			return;
		}

	#ifdef LN_PLATFORM_WINDOWS
		CHAR_INFO c = sourceChar.Translate_Win();
	#endif

		screenBuffer[y * width + x] = c;
	}
}
