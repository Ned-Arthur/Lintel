#pragma once

#include "Core.h"

#include <windows.h>


// The windows implementation only supports 8/16 colours, so we'll keep that
// limitation for the whole render pipeline
enum TermColour {
	BLACK,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,
	CYAN,
	WHITE,
	// I_ for Intense
	I_BLACK,
	I_RED,
	I_GREEN,
	I_BLUE,
	I_YELLOW,
	I_MAGENTA,
	I_CYAN,
	I_WHITE
};

namespace Lintel {

	struct TChar {
		TChar(char _c, TermColour _fg_col, TermColour _bg_col) : c(_c), fg_col(_fg_col), bg_col(_bg_col) {}
		char c;
		TermColour fg_col;
		TermColour bg_col;
		// None of the windows grid attributes seem to work, so that's all we need

	#ifdef LN_PLATFORM_WINDOWS
		CHAR_INFO Translate_Win();
	#endif
	};

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

		void resize(int w, int h);
		void redraw();
		void flushBuffer(TChar blankChar);
		void drawChar(TChar c, int x, int y);
	private:
		int width;
		int height;

		// Platform specific implementation
	#ifdef LN_PLATFORM_WINDOWS
		CHAR_INFO* screenBuffer;
		HANDLE wHnd;				// Handle for window writing
		HANDLE rHnd;				// Handle for window reading
		SMALL_RECT srctWriteRect;
		COORD coordBufSize;
		COORD coordBufCoord;
	#endif
	};
}
