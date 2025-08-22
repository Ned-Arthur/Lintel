#pragma once

#include "TChar.h"
#include "TSprite.h"
#include "TThing.h"

#include <list>
#include <vector>
#include <unordered_set>
#include <string>

#include <windows.h>

namespace Lintel {
	class Application;
	// A Terminal Renderer
	// Primarily uses ANSI escape codes to draw text to whatever terminal the
	// user is running. While not completely universal, at least windows cmd
	// and most linux terminals should work OK with this.
	class TRen
	{
	public:
		TRen();
		~TRen();

		// Static methods
		static void GetConsoleSize(int* x, int* y);

		bool WantsToQuit = false;

		// Entity system (should this be here? probably not)
		std::list<TThing*> Things;
		template <typename T> T* CreateThing(std::string name = "", std::unordered_set<std::string> tags = {});
		TThing* GetThingByName(std::string name);
		std::vector<TThing*> GetThingsWithTag(std::string tag);

		void QuitApp();

		// Setup methods
		void SetTitle(const char* termTitle);
		void SetBackgroundCharacter(TChar bgChar);
		void SetBackgroundSprite(std::string spritePath);

		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }

		// Drawing methods
		void FillBufferWithCharacter(TChar blankChar);
		void DrawString(const char* message, TChar templateCharacter, int32_t x, int32_t y);
		void DrawString(const char* message, TermColour foregroundColour, TermColour backgroundColour, int32_t x, int32_t y);
		void DrawSprite(TSprite sprite, int32_t x, int32_t y);
		void DrawCharacter(TChar character, int32_t x, int32_t y);

	private:
		void DrawCharacterUnsafe(TChar character, int32_t x, int32_t y);
		
		// Doesn't actually resize the window, but the virtual drawing space
		// The user should not use this, because it will just act weird and not
		// actually "resize" the window
		void ResizeBuffer(int w, int h);
		void SetupThings();
		// Non-drawing loop methods
		void GatherInput();
		void UpdateAndDraw();

		int m_Width;
		int m_Height;

		TChar* m_ScreenBuffer;

		bool m_UsingBackgroundSprite;
		TChar m_BackgroundCharacter;
		TSprite m_BackgroundSprite;

		bool m_ThingsAreSetup = false;

		// Platform specific implementation data
	#ifdef LN_PLATFORM_WINDOWS
		CHAR_INFO* m_WindowsScreenBuffer;
		HANDLE m_wHnd;				// Handle for window writing
		HANDLE m_rHnd;				// Handle for window reading
		SMALL_RECT m_srctWriteRect;
		COORD m_coordBufSize;
		COORD m_coordBufCoord;
		CONSOLE_CURSOR_INFO m_oldCI;	// To restore the console after closing
	#endif

		friend Application;
	};


	template<typename T>
	inline T* TRen::CreateThing(std::string name, std::unordered_set<std::string> tags)
	{
		T* newThing = new T(this, name, tags);
		Things.push_back(newThing);

		if (m_ThingsAreSetup)
		{
			newThing->Setup();
		}

		return newThing;
	}
}
