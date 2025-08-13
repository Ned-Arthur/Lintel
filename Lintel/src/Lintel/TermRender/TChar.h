#pragma once

#include <windows.h>
// windows.h defines this as 1, but we don't need it. I'll see me around when
// this inevitably breaks everything
#undef TRANSPARENT

namespace Lintel {

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
		I_WHITE,

		TRANSPARENT		// Take the colour from the char underneath this
	};

	struct TChar
	{
		TChar(char _c, TermColour _fg_col, TermColour _bg_col) : c(_c), fg_col(_fg_col), bg_col(_bg_col) {}
		TChar() : c('a'), fg_col(WHITE), bg_col(BLACK) {}

		char c;
		TermColour fg_col;
		TermColour bg_col;
		// None of the windows grid attributes seem to work, so that's all we need

#ifdef LN_PLATFORM_WINDOWS
		CHAR_INFO Translate_Win();
#endif
	};

}

