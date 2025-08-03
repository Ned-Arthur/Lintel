#pragma once

#include "TChar.h"

struct TChar;
enum TermColour;

namespace Lintel {

	//TODO figure out what we can make private
	class TSprite
	{
	public:
		void setSpriteFromString(const char* spriteData, int w, int h, TermColour fg, TermColour bg);
		void loadSprite(const char* filepath);

		TChar getCharAtPosition(int x, int y);
		int getWidth();
		int getHeight();

	private:
		int width;
		int height;

		TChar* spriteData;
	};

}
