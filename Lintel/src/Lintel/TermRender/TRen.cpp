#include "TRen.h"

#include "Input.h"

// Platform specific implementations are better suited to the source I think;
// none of this is needed by users or will be needed outside this file

// Colour translation tables
#ifdef LN_PLATFORM_WINDOWS
constexpr int TCTransFG_Win[16] = {
	0,
	FOREGROUND_RED,
	FOREGROUND_GREEN,
	FOREGROUND_BLUE,
	FOREGROUND_RED | FOREGROUND_GREEN,
	FOREGROUND_RED | FOREGROUND_BLUE,
	FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

	FOREGROUND_INTENSITY,
	FOREGROUND_INTENSITY | FOREGROUND_RED,
	FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};
constexpr int TCTransBG_Win[16] = {
	0,
	BACKGROUND_RED,
	BACKGROUND_GREEN,
	BACKGROUND_BLUE,
	BACKGROUND_RED | BACKGROUND_GREEN,
	BACKGROUND_RED | BACKGROUND_BLUE,
	BACKGROUND_GREEN | BACKGROUND_BLUE,
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,

	BACKGROUND_INTENSITY,
	BACKGROUND_INTENSITY | BACKGROUND_RED,
	BACKGROUND_INTENSITY | BACKGROUND_GREEN,
	BACKGROUND_INTENSITY | BACKGROUND_BLUE,
	BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
	BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
	BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
};
#endif

namespace Lintel {
#ifdef LN_PLATFORM_WINDOWS
	CHAR_INFO TChar::Translate_Win()
	{
		CHAR_INFO ret;
		ret.Char.AsciiChar = Character;
		ret.Attributes = TCTransFG_Win[ForegroundColour] | TCTransBG_Win[BackgroundColour];
		return ret;
	}
#endif

	TRen::TRen()
	{
		GetConsoleSize(&m_Width, &m_Height);
		m_ScreenBuffer = new TChar[m_Width * m_Height];

	#ifdef LN_PLATFORM_WINDOWS
		m_WindowsScreenBuffer = new CHAR_INFO[m_Width * m_Height];

		m_wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
		m_rHnd = GetStdHandle(STD_INPUT_HANDLE);

		m_coordBufCoord.X = 0;
		m_coordBufCoord.Y = 0;

		m_coordBufSize.Y = m_Height;
		m_coordBufSize.X = m_Width;

		m_srctWriteRect.Top = 0;
		m_srctWriteRect.Left = 0;
		m_srctWriteRect.Bottom = m_Height;
		m_srctWriteRect.Right = m_Width;

		GetConsoleCursorInfo(m_wHnd, &m_oldCI);
		CONSOLE_CURSOR_INFO ci = m_oldCI;
		ci.bVisible = FALSE;
		SetConsoleCursorInfo(m_wHnd, &ci);

	#endif
	}

	TRen::~TRen()
	{
		// Free all the memory for our TThing s
		for (auto const& thing : Things)
		{
			delete thing;
		}
		Things.clear();

		delete[] m_ScreenBuffer;

	#ifdef LN_PLATFORM_WINDOWS
		delete[] m_WindowsScreenBuffer;

		// Revert the console settings so it can be used as normal after being closed
		// TODO? Clear the console graphics as well
		SetConsoleCursorInfo(m_wHnd, &m_oldCI);
	#endif
	}

/*********** Entity System ***********/
	void TRen::SetupThings()
	{
		for (auto const& thing : Things)
		{
			thing->Setup();
		}

		m_ThingsAreSetup = true;
	}

	TThing* TRen::GetThingByName(std::string name)
	{
		for (auto const& thing : Things)
		{
			if (thing->Name() == name)
			{
				return thing;
			}
		}
		return nullptr;
	}

	std::vector<TThing*> TRen::GetThingsWithTag(std::string tag)
	{
		std::vector<TThing*> foundThings;
		
		for (auto const& thing : Things)
		{
			if (thing->m_Tags.contains(tag))
			{
				foundThings.push_back(thing);
			}
		}

		return foundThings;
	}

	void TRen::QuitApp()
	{
		WantsToQuit = true;
	}

	
/*********** Static Methods ***********/
	void TRen::GetConsoleSize(int* columns, int* rows)
	{
	#ifdef LN_PLATFORM_WINDOWS
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		*columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		*rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	#endif
	}


/*********** Setup ***********/
	void TRen::SetTitle(const char* termTitle)
	{
	#ifdef LN_PLATFORM_WINDOWS
		// Be naughty and use the ANSI function so we don't need to do a conversion
		SetConsoleTitleA(termTitle);
	#endif
	}

	void TRen::SetBackgroundCharacter(TChar bgChar)
	{
		m_BackgroundCharacter = bgChar;
		m_UsingBackgroundSprite = false;
	}

	void TRen::SetBackgroundSprite(std::string spritePath)
	{
		m_BackgroundSprite.SetSpriteFromFile(spritePath.c_str());
		m_UsingBackgroundSprite = true;
	}


/*********** Compulsory Loop Methods ***********/
	void TRen::GatherInput()
	{
	#ifdef LN_PLATFORM_WINDOWS
		// Handle (console) window events
		DWORD numEvents = 0;
		DWORD numEventsRead = 0;
		GetNumberOfConsoleInputEvents(m_rHnd, &numEvents);
		if (numEvents != 0)
		{
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(m_rHnd, eventBuffer, numEvents, &numEventsRead);

			for (DWORD i = 0; i < numEventsRead; ++i)
			{
				switch (eventBuffer[i].EventType)
				{
				case KEY_EVENT:
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_ESCAPE:
						Input::SetKeyState(K_ESCAPE, eventBuffer[i].Event.KeyEvent.bKeyDown);

						break;
					}

					Input::SetKeyState(eventBuffer[i].Event.KeyEvent.uChar.AsciiChar, eventBuffer[i].Event.KeyEvent.bKeyDown);

					break;
				case WINDOW_BUFFER_SIZE_EVENT:
					COORD newSize = eventBuffer[i].Event.WindowBufferSizeEvent.dwSize;
					// Update all our variables to store & draw at the right sizes
					ResizeBuffer(newSize.X, newSize.Y);
				}
			}

			delete[] eventBuffer;
		}
	#endif
	}

	void TRen::UpdateAndDraw()
	{
		// Clear the background
		if (m_UsingBackgroundSprite)
		{
			// integer division floors, but we'd rather draw extra background outside
			// the window over blank edges
			int repeatX = m_Width / m_BackgroundSprite.GetWidth() + 1;
			int repeatY = m_Height / m_BackgroundSprite.GetHeight() + 1;

			for (int i = 0; i < repeatX; i++)
			{
				for (int j = 0; j < repeatY; j++)
				{
					DrawSprite(m_BackgroundSprite,
						i * m_BackgroundSprite.GetWidth(),
						j * m_BackgroundSprite.GetHeight()
					);
				}
			}
		}
		else
		{
			FillBufferWithCharacter(m_BackgroundCharacter);
		}

		// Update all our TThings and delete those we don't need
		std::list<TThing*>::iterator iter = Things.begin();

		while (iter != Things.end())
		{
			(*iter)->Update();

			if ((*iter)->MarkedForDeletion())
			{
				iter = Things.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		for (auto const& thing : Things)
		{
			thing->Draw();
		}

		// Draw the character buffer to the console
	#ifdef LN_PLATFORM_WINDOWS
		// Translate the platform-independent buffer to something windows understands
		for (int i = 0; i < m_Width * m_Height; i++)
		{
			m_WindowsScreenBuffer[i] = m_ScreenBuffer[i].Translate_Win();
		}
		
		// Use ANSI method so we don't have to deal with conversion bs and can
		// just use ASCII/ANSI chars in App and maintain cross-platform-ness
		WriteConsoleOutputA(
			m_wHnd,
			m_WindowsScreenBuffer,
			m_coordBufSize,
			m_coordBufCoord,
			&m_srctWriteRect);
	#endif
	}


/*********** Drawing Methods ***********/
	void TRen::FillBufferWithCharacter(TChar blankChar)
	{
		for (int i = 0; i < m_Width * m_Height; i++)
		{
			m_ScreenBuffer[i] = blankChar;
		}
	}

	void TRen::DrawString(const char* message, TChar templateCharacter, int32_t x, int32_t y)
	{
		for (int i = 0; i < strlen(message); i++)
		{
			templateCharacter.Character = message[i];
			DrawCharacter(templateCharacter, x + i, y);
		}
	}
	void TRen::DrawString(const char* message, TermColour foregroundColour, TermColour backgroundColour, int32_t x, int32_t y)
	{
		for (int i = 0; i < strlen(message); i++)
		{
			DrawCharacter(TChar(message[i], foregroundColour, backgroundColour), x + i, y);
		}
	}

	void TRen::DrawSprite(TSprite sprite, int32_t x, int32_t y)
	{
		// Check the bounds first so we can avoid bounds-checking every char
		int w = sprite.GetWidth();
		int h = sprite.GetHeight();

		int wStart = 0;
		int hStart = 0;

		// Pre-check all of our bounds so we can drawUnsafe
		if (x < 0)
			wStart -= x;
		if (y < 0)
			hStart -= y;
		if (x + w > m_Width)
			w -= (x + w) - m_Width;
		if (y + h > m_Height)
			h -= (y + h) - m_Height;
		
		for (int i = wStart; i < w; i++)
		{
			for (int j = hStart; j < h; j++)
			{
				// Get the char we're about to draw over
				TChar underneath = m_ScreenBuffer[(x + i) + (y + j) * m_Width];

				DrawCharacterUnsafe(sprite.GetCharacterAtPosition(i, j, underneath), x + i, y + j);
			}
		}
	}

	void TRen::DrawCharacter(TChar character, int32_t x, int32_t y)
	{
		if (x >= m_Width || y >= m_Height || x < 0 || y < 0)
		{
			return;
		}

		DrawCharacterUnsafe(character, x, y);
	}
	void TRen::DrawCharacterUnsafe(TChar character, int32_t x, int32_t y)
	{
		m_ScreenBuffer[y * m_Width + x] = character;
	}

/*********** Private Control ***********/
	void TRen::ResizeBuffer(int w, int h)
	{
		m_Width = w;
		m_Height = h;

		delete[] m_ScreenBuffer;
		m_ScreenBuffer = new TChar[m_Width * m_Height];

#ifdef LN_PLATFORM_WINDOWS
		delete[] m_WindowsScreenBuffer;
		m_WindowsScreenBuffer = new CHAR_INFO[m_Width * m_Height];

		m_coordBufSize.Y = m_Height;
		m_coordBufSize.X = m_Width;

		m_srctWriteRect.Bottom = m_Height;
		m_srctWriteRect.Right = m_Width;
#endif
	}
}
