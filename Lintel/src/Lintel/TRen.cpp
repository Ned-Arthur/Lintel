#include "TRen.h"

#include <cstdio>

namespace Lintel {
	TRen::TRen()
	{
	#ifdef LN_PLATFORM_WINDOWS
		// Size the console
		getConsoleSize(&width, &height);
		screenBuffer = new CHAR_INFO[width * height];

		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

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
			hStdout,
			screenBuffer,
			coordBufSize,
			coordBufCoord,
			&srctWriteRect);
	#endif
 	}

	void TRen::flushBuffer(CHAR_INFO blankChar)
	{
		for (int i = 0; i < width * height; i++)
		{
			screenBuffer[i] = blankChar;
		}
		
	}

	void TRen::drawChar(CHAR_INFO c, int x, int y)
	{
		if (x >= width || y >= height)
		{
			return;
		}

		screenBuffer[y * width + x] = c;
	}

	void TRen::clear()
	{
		// Clear entire console, reset cursor to top-left
		printf("\x1b[2J\x1b[H");
	}

}
