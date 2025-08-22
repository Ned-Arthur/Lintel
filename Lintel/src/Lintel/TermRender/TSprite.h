#pragma once

#include <stdint.h>
#include "TChar.h"

namespace Lintel {

	class TSprite
	{
	public:
		void SetSpriteFromString(const char* spriteData, uint16_t spriteWidth, uint16_t spriteHeight, TermColour foregroundColour, TermColour backgroundColour);
		void SetSpriteFromFile(const char* filepath);
		void RecolourFullSprite(TermColour foregroundColour, TermColour backgroundColour);

		TChar GetCharacterAtPosition(uint16_t x, uint16_t y, TChar underneath);
		uint16_t GetWidth();
		uint16_t GetHeight();

	private:
		uint16_t m_Width;
		uint16_t m_Height;

		TChar* m_SpriteData;
	};

}
