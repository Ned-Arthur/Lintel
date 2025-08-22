#include "lnpch.h"
#include "TSprite.h"

namespace Lintel {
	void TSprite::SetSpriteFromString(const char* spriteText, uint16_t spriteWidth, uint16_t spriteHeight,
										TermColour foregroundColour, TermColour backgroundColour)
	{
		m_Width = spriteWidth;
		m_Height = spriteHeight;
		m_SpriteData = new TChar[m_Width * m_Height];
		
		for (size_t columnIndex = 0; columnIndex < m_Width; columnIndex++)
		{
			for (size_t rowIndex = 0; rowIndex < m_Height; rowIndex++)
			{
				m_SpriteData[columnIndex + rowIndex * m_Width] = TChar(spriteText[columnIndex + rowIndex * m_Width], foregroundColour, backgroundColour);
			}
		}
	}

	std::unordered_map<std::string, TermColour> stringToTermColour = {
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
		{"I_WHITE", I_WHITE},
		{"TRANSPARENT", TRANSPARENT}
	};

	void TSprite::SetSpriteFromFile(const char* filepath)
	{
		uint16_t spriteRowIndex = 0;
		TermColour foregroundColour, backgroundColour;
		
		// Process the file by-line
		std::string lineBuffer;
		std::ifstream spriteFile(filepath);
		while (std::getline(spriteFile, lineBuffer))
		{
			// Skip over boilerplate lines
			if (lineBuffer == "LINTEL-SPRITE" || lineBuffer.empty())
				continue;

			// Using just two colours ('mono'chrome)
			if (lineBuffer.substr(0, 4) == "MONO")
			{
				// These buffers must be sized [longest colour name + 1]
				char foregroundColourBuffer[12], backgroundColourBuffer[12];
				sscanf(lineBuffer.c_str(), "MONO: %s %s", foregroundColourBuffer, backgroundColourBuffer);
				
				foregroundColour = stringToTermColour[foregroundColourBuffer];
				backgroundColour = stringToTermColour[backgroundColourBuffer];
				
				continue;
			}

			// If the user declares multiple SIZE attributes they'll cause a memory leak
			// by declaring new arrays for each one then losing the pointer.
			// Sucks to be them
			if (lineBuffer.substr(0, 4) == "SIZE")
			{
				sscanf(lineBuffer.c_str(), "SIZE: %d %d", &m_Width, &m_Height);
				m_SpriteData = new TChar[m_Width * m_Height];
				continue;
			}

			// If we get here we're handling sprite data
			for (int i = 0; i < m_Width; i++)
			{
				m_SpriteData[i + spriteRowIndex * m_Width] = TChar(lineBuffer[i], foregroundColour, backgroundColour);
			}

			spriteRowIndex++;
		}

		// Clean up
		spriteFile.close();
	}

	void TSprite::RecolourFullSprite(TermColour foregroundColour, TermColour backgroundColour)
	{
		for (int i = 0; i < m_Width * m_Height; i++)
		{
			m_SpriteData[i].ForegroundColour = foregroundColour;
			m_SpriteData[i].BackgroundColour = backgroundColour;
		}
	}

	TChar TSprite::GetCharacterAtPosition(uint16_t x, uint16_t y, TChar underneath)
	{
		// Guard bad reads and return an error char
		if (x > m_Width || y > m_Height) return TChar(0x9d, I_RED, I_WHITE);
		TChar characterData = m_SpriteData[x + y * m_Width];
		
		// Handle transparent colours
		if (characterData.ForegroundColour == TRANSPARENT)
			characterData.ForegroundColour = underneath.ForegroundColour;
		if (characterData.BackgroundColour == TRANSPARENT)
		{
			if (characterData.Character == ' ')
			{
				// The background is transparent and there's no foreground
				characterData = underneath;
			}
			else
			{
				characterData.BackgroundColour = underneath.BackgroundColour;
			}
		}

		return characterData;
	}
	
	uint16_t TSprite::GetWidth()
	{
		return m_Width;
	}
	uint16_t TSprite::GetHeight()
	{
		return m_Height;
	}
}
