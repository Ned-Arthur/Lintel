#pragma once

#include "TChar.h"

namespace Lintel {

	//TODO figure out what we can make private
	class TSprite
	{
	public:
		void setSpriteFromString(const char* spriteData, int w, int h, TermColour fg, TermColour bg);
		void loadSprite(const char* filepath);

		TChar getCharAtPosition(int x, int y, TChar underneath);
		int getWidth();
		int getHeight();

	private:
		int width;
		int height;

		TChar* spriteData;
	};

}
