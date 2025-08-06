#pragma once

#include "TSprite.h"
#include "TVec.h"

#include <string>

namespace Lintel {
	class TRen;

	class TThing
	{
	public:
		TThing(TRen* _renderer, std::string _name);

		/* Overridable functions for app - space control */
		void genericSetup();
		// Set spriteFilePath, other members, and get references to other things
		// Named things exist here, but aren't guaranteed to have values
		virtual void Setup() = 0;
		// Optional setup based on values from other Things. All Setup has been
		// completed when this is called
		virtual void LateSetup() {}
		// Called every frame, take input and do movement
		virtual void Update() = 0;
		
		/* Pseudo - protected members, but need to access from other Things */
		std::string name;			// Identification for other Things
		TVec<float> pos;			// Position on the screen
		TVec<int> spriteCenter;		// Position in sprite coordinates that pos represents in screen-space
		bool visible = true;		// Do we draw the sprite?

		const char* spriteFilePath;	// Which sprite to load after setup
		TRen* renderer;				// Pointer to the renderer for sprite drawing

		// This is only called by the engine
		void Draw();

	private:
		TSprite sprite;
	};
}
