#include "TRen.h"

#include <windows.h>
#include <stdio.h>
#include <cstdlib>

#include <stdexcept>

namespace Lintel {
	TRen::TRen()
	{
		// allocate memory for the buffer for certain
		screenBuffer = (char*)malloc(sizeof(char));
		width = 1;
		height = 1;
	}
	TRen::~TRen()
	{
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
		free(screenBuffer);
		screenBuffer = (char*)malloc(sizeof(char) * width * height);

		clear();
	}

	void TRen::redraw()
	{
		clear();

		printf("%s", screenBuffer);
	}

	void TRen::fillBuffer(char* newBuf)
	{
		for (int i = 0; i < width * height; i++)
		{
			screenBuffer[i] = newBuf[i];
		}
	}

	void TRen::flushBuffer(char blankChar)
	{
		for (int i = 0; i < width * height; i++)
		{
			screenBuffer[i] = blankChar;
		}
		
	}

	void TRen::drawChar(char c, int x, int y)
	{
		if (x > width - 1 || y > height - 1)
		{
			throw std::runtime_error("Tried to write a char outside the buffer size");
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
