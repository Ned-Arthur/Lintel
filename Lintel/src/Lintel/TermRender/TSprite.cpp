#include "TSprite.h"

#include <string>
#include <fstream>
#include <unordered_map>

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
				spriteData[i + j * width] = TChar(spriteText[i + j * width], fg, bg);
			}
		}
	}

	std::unordered_map<std::string, TermColour> strToTC = {
		{"BLACK", BLACK},
		{"RED", RED},
		{"GREEN", GREEN},
		{"BLUE", BLUE},
		{"YELLOW", YELLOW},
		{"MAGENTA", MAGENTA},
		{"CYAN", CYAN},
		{"WHITE", WHITE},
		{"I_BLACK", I_BLACK},
		{"I_RED", I_RED},
		{"I_GREEN", I_GREEN},
		{"I_BLUE", I_BLUE},
		{"I_YELLOW", I_YELLOW},
		{"I_MAGENTA", I_MAGENTA},
		{"I_CYAN", I_CYAN},
		{"I_WHITE", I_WHITE}
	};

	void TSprite::loadSprite(const char* filepath)
	{
		int row = 0;
		TermColour fg, bg;
		
		// Process the file by-line
		std::string buffer;
		std::ifstream spriteFile(filepath);
		while (std::getline(spriteFile, buffer))
		{
			// Skip over boilerplate lines
			if (buffer == "LINTEL-SPRITE" || buffer.empty())
				continue;

			// Using just two colours ('mono'chrome)
			if (buffer.substr(0, 4) == "MONO")
			{
				char fgColStr[10], bgColStr[10];
				sscanf(buffer.c_str(), "MONO: %s %s", fgColStr, bgColStr);
				
				fg = strToTC[fgColStr];
				bg = strToTC[bgColStr];
				
				continue;
			}

			// If the user declares multiple SIZE attributes they'll cause a memory leak
			// by declaring new arrays for each one then losing the pointer.
			// Sucks to be them
			if (buffer.substr(0, 4) == "SIZE")
			{
				sscanf(buffer.c_str(), "SIZE: %d %d", &width, &height);
				spriteData = new TChar[width * height];
				continue;
			}

			// If we get here we're handling sprite data
			for (int i = 0; i < width; i++)
			{
				spriteData[i + row * width] = TChar(buffer[i], fg, bg);
			}

			row++;
		}

		// Clean up
		spriteFile.close();
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
