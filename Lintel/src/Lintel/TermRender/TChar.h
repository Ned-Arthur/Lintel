#pragma once

#include <windows.h>
// windows.h defines this as 1, but we don't need it. I'll see me around when
// this inevitably breaks everything
#undef TRANSPARENT

namespace Lintel {

	// The windows implementation only supports 16 colours, so we'll keep that
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
		TChar(char character='a', TermColour foregroundColour=WHITE, TermColour backgroundColour=BLACK)
			: Character(character), ForegroundColour(foregroundColour), BackgroundColour(backgroundColour) {}

		char Character;
		TermColour ForegroundColour;
		TermColour BackgroundColour;
		// None of the windows grid attributes seem to work, so that's all we need

#ifdef LN_PLATFORM_WINDOWS
		CHAR_INFO Translate_Win();
#endif
	};

}

