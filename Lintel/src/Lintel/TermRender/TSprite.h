#pragma once

#include "TChar.h"

namespace Lintel {

	class TSprite
	{
	public:
		void setSpriteFromString(const char* spriteData, int w, int h, TermColour fg, TermColour bg);
		void loadSprite(const char* filepath);
		void recolour(TermColour fg, TermColour bg);

		TChar getCharAtPosition(int x, int y, TChar underneath);
		int getWidth();
		int getHeight();

	private:
		int width;
		int height;

		TChar* spriteData;
	};

}
