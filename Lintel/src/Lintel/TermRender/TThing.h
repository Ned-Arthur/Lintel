#pragma once

#include "TSprite.h"
#include "TVec.h"

#include <string>
#include <vector>
#include <unordered_set>

namespace Lintel {
	class TRen;

	enum EdgeDirection {
		LEFT,
		TOP,
		RIGHT,
		BOTTOM,
	};

	class TThing
	{
	public:
		TThing(TRen* _renderer, std::string _name, std::unordered_set<std::string> _tags);

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
		std::string name;						// Unique identification for other Things
		std::unordered_set<std::string> tags;	// Generic ID shared among many Things
		TVec<float> pos = { 0,0 };				// Position on the screen
		TVec<int> spriteCenter = { 0,0 };		// Position in sprite coordinates that pos represents in screen-space
		bool visible = true;					// Do we draw the sprite?

		// Initialise the position once, any extra calls will be ignored
		void initPos(TVec<float> startPos);
		void initSpriteFP(const char* filePath);

		void QueueDelete();
		bool MarkedForDeletion();

		/* Helper functions for intersections etc. */
		bool isIntersecting(TThing* other);
		int getBound(EdgeDirection dir);
		bool moveByAndCollideWith(float dx, float dy, std::string solidTag, bool collideWithScreenEdges=false);

		TSprite* Sprite();

		const char* spriteFilePath = "NONE";	// Which sprite to load after setup
		TRen* renderer;							// Pointer to the renderer for sprite drawing

		// This is only called by the engine
		void Draw();

	private:
		TSprite sprite;
		bool posInitialised = false;
		bool spriteInitialised = false;
		bool shouldDelete = false;
	};
}
