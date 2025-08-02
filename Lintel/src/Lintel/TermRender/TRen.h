#pragma once

#include "../Core.h"

#include "TChar.h"
#include "TSprite.h"

#include <windows.h>

namespace Lintel {
	// A Terminal Renderer
	// Primarily uses ANSI escape codes to draw text to whatever terminal the
	// user is running. While not completely universal, at least windows cmd
	// and most linux terminals should work OK with this.
	class LINTEL_API TRen
	{
	public:
		TRen();
		~TRen();

		static void getConsoleSize(int* x, int* y);

		void setTitle(const char* termTitle);

		void update(int* gameW, int* gameH);
		void resize(int w, int h);
		void redraw();
		void flushBuffer(TChar blankChar);
		void drawChar(TChar c, int x, int y);
		void drawMsg(const char* msg, TChar temp, int x, int y);
		void drawMsg(const char* msg, TermColour fgColour, TermColour bgColour, int x, int y);
		void drawSprite(TSprite sprite, int x, int y);
	private:
		void drawCharUnsafe(TChar sourceChar, int x, int y);

		int width;
		int height;

		// Platform specific implementation data
	#ifdef LN_PLATFORM_WINDOWS
		CHAR_INFO* screenBuffer;
		HANDLE wHnd;				// Handle for window writing
		HANDLE rHnd;				// Handle for window reading
		SMALL_RECT srctWriteRect;
		COORD coordBufSize;
		COORD coordBufCoord;
		CONSOLE_CURSOR_INFO oldCI;	// To restore the console after closing
	#endif
	};
}
