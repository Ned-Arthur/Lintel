#include "TSprite.h"

namespace Lintel {
	void TSprite::setSpriteFromString(const char* spriteText, int w, int h, TermColour fg, TermColour bg)
	{
		width = w;
		height = h;
		spriteData = new TChar[width * height];
		
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				spriteData[i + j * height] = TChar(spriteText[i + j * height], fg, bg);
			}
		}
	}
	TChar TSprite::getCharAtPosition(int x, int y)
	{
		// Guard bad reads and return an error char
		if (x > width || y > height) return TChar(0x9d, I_RED, I_WHITE);
		return spriteData[x + y * width];
	}
	int TSprite::getWidth()
	{
		return width;
	}
	int TSprite::getHeight()
	{
		return height;
	}
}
