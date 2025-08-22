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
		TThing(TRen* renderer, std::string name, std::unordered_set<std::string> tags);

		/* Overridable functions for app - space control */
		virtual void Setup() = 0;
		virtual void Update() = 0;

		// Initialise fields once and only once
		void InitPosition(TVec<float> startPos);
		void InitSprite(const char* filePath);
		void InitSpriteCenter(TVec<int> _spriteCenter);

		void SetVisibility(bool visibility);

		std::string Name() { return m_Name; }
		std::unordered_set<std::string>* Tags() { return &m_Tags; }
		TSprite* Sprite() { return &m_Sprite; }

		void QueueDelete();
		bool MarkedForDeletion();

		/* Physics */
		bool IsIntersecting(TThing* other);
		bool MoveByAndCollideWith(float dx, float dy, std::string solidTag, bool collideWithScreenEdges=false);

		TRen* Renderer;		// The renderer which owns this TThing
		TVec<float> Position = { 0, 0 };	// Position on the screen

	private:
		void Draw();

		int GetBound(EdgeDirection dir);

		TSprite m_Sprite;
		std::string m_Name;						// Unique identification for other Things
		std::unordered_set<std::string> m_Tags;	// Generic ID shared among many Things
		TVec<int> m_SpriteCenter = { 0, 0 };		// Position in sprite coordinates that Position represents in screen-space

		bool m_Visible = true;
		bool m_FlaggedForDeletion = false;

		// Initialisation flags
		bool m_PositionInitialised = false;
		bool m_SpriteInitialised = false;
		bool m_SpriteCenterInitialised = false;

		friend TRen;
	};
}
