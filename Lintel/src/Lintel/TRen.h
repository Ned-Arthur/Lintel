#pragma once

#include "Core.h"

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

		void resize(int w, int h);
		void redraw();
		void fillBuffer(char* newBuf);
		void flushBuffer(char blankChar);
		void drawChar(char c, int x, int y);
	private:
		void clear();

		int width;
		int height;
		char* screenBuffer;
	};

}
