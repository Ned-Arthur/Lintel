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
	// A Terminal Renderer
	// Primarily uses ANSI escape codes to draw text to whatever terminal the
	// user is running. While not completely universal, at least windows cmd
	// and most linux terminals should work OK with this.
	class TRen
	{
	public:
		TRen();
		~TRen();

		bool wantsToQuit = false;

		// Entity system (should this be here? probably not)
		std::list<TThing*> things;
		template <typename T> T* createThing(std::string name = "", std::unordered_set<std::string> tags = {});
		void setupThings();
		TThing* getThingByName(std::string name);
		std::vector<TThing*> getThingsWithTag(std::string tag);

		void QuitApp();

		// Static methods
		static void getConsoleSize(int* x, int* y);

		// Setup methods
		void setTitle(const char* termTitle);
		void setBG(TChar bgChar);
		void setBGSprite(std::string spritePath);

		// Non-drawing loop methods
		void GatherInput();
		void UpdateAndDraw();

		int getWidth() { return width; }
		int getHeight() { return height; }

		// Drawing methods
		void flushBuffer(TChar blankChar);
		void drawMsg(const char* msg, TChar temp, int x, int y);
		void drawMsg(const char* msg, TermColour fgColour, TermColour bgColour, int x, int y);
		void drawSprite(TSprite sprite, int x, int y);
		void drawChar(TChar c, int x, int y);

	private:
		void drawCharUnsafe(TChar sourceChar, int x, int y);
		
		// Doesn't actually resize the window, but the virtual drawing space
		// The user should use this, because it will just act weird and not
		// actually "resize" the window
		void resize(int w, int h);

		int width;
		int height;

		TChar* screenBuffer;

		bool usingSprite;
		TChar backgroundChar;
		TSprite backgroundSprite;

		bool isSetup = false;

		// Platform specific implementation data
	#ifdef LN_PLATFORM_WINDOWS
		CHAR_INFO* win_screenBuffer;
		HANDLE wHnd;				// Handle for window writing
		HANDLE rHnd;				// Handle for window reading
		SMALL_RECT srctWriteRect;
		COORD coordBufSize;
		COORD coordBufCoord;
		CONSOLE_CURSOR_INFO oldCI;	// To restore the console after closing
	#endif
	};


	template<typename T>
	inline T* TRen::createThing(std::string name, std::unordered_set<std::string> tags)
	{
		T* newThing = new T(this, name, tags);
		things.push_back(newThing);

		if (isSetup)
		{
			newThing->genericSetup();
			newThing->LateSetup();
		}

		return newThing;
	}
}
