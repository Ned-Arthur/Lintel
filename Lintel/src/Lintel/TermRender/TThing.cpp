#include "TThing.h"

#include "TRen.h"

namespace Lintel {
	TThing::TThing(TRen* renderer, std::string name, std::unordered_set<std::string> tags)
		: Renderer(renderer), m_Name(name), m_Tags(tags)
	{}

	void TThing::InitPosition(TVec<float> startPos)
	{
		if (!m_PositionInitialised)
		{
			Position = startPos;
			m_PositionInitialised = true;
		}
	}

	void TThing::InitSprite(const char* filePath)
	{
		if (!m_SpriteInitialised)
		{
			m_Sprite.SetSpriteFromFile(filePath);
			m_SpriteInitialised = true;
		}
	}

	void TThing::InitSpriteCenter(TVec<int> _spriteCenter)
	{
		if (!m_SpriteCenterInitialised)
		{
			m_SpriteCenter = _spriteCenter;
			m_SpriteCenterInitialised = true;
		}
	}

	void TThing::SetVisibility(bool visibility)
	{
		m_Visible = visibility;
	}

	void TThing::QueueDelete()
	{
		m_FlaggedForDeletion = true;
	}

	bool TThing::MarkedForDeletion()
	{
		return m_FlaggedForDeletion;
	}

	// Basic rectangle intersection
	bool TThing::IsIntersecting(TThing* other)
	{
		int totalSpriteWidth = GetBound(RIGHT) - GetBound(LEFT) + other->GetBound(RIGHT) - other->GetBound(LEFT);
		int totalSpriteHeight = GetBound(BOTTOM) - GetBound(TOP) + other->GetBound(BOTTOM) - other->GetBound(TOP);

		

		int topMostChar = min(GetBound(TOP), other->GetBound(TOP));
		int bottomMostChar = max(GetBound(BOTTOM), other->GetBound(BOTTOM));
		int boundingRectHeight = bottomMostChar - topMostChar;

		int leftMostChar = min(GetBound(LEFT), other->GetBound(LEFT));
		int rightMostChar = max(GetBound(RIGHT), other->GetBound(RIGHT));
		int boundingRectWidth = rightMostChar - leftMostChar;

		if (boundingRectHeight < totalSpriteHeight && boundingRectWidth < totalSpriteWidth)
		{
			return true;
		}
		return false;
	}

	int TThing::GetBound(EdgeDirection dir)
	{
		switch (dir)
		{
		case LEFT:
			return Position.x - m_SpriteCenter.x;
		case RIGHT:
			return Position.x - m_SpriteCenter.x + m_Sprite.GetWidth();
		case TOP:
			return Position.y - m_SpriteCenter.y;
		case BOTTOM:
			return Position.y - m_SpriteCenter.y + m_Sprite.GetHeight();
		}
		
		return -1;
	}

	// Move by (dx, dy), colliding with / sliding along TThings with `solidTag` (and optionally screen edges)
	// Returns whether a collision occured
	bool TThing::MoveByAndCollideWith(float dx, float dy, std::string solidTag, bool collideWithScreenEdges)
	{
		std::vector<TThing*> solidProps = Renderer->GetThingsWithTag("solid");
		
		Position.x += dx;
		bool revertX = false;
		for (TThing* p : solidProps)
		{
			if (p == this) continue;
			if (IsIntersecting(p))
			{
				revertX = true;
			}
		}
		if (collideWithScreenEdges && (GetBound(LEFT) < 0 || GetBound(RIGHT) > Renderer->GetWidth()))
		{
			revertX = true;
		}
		if (revertX)
		{
			Position.x -= dx;
		}

		Position.y += dy;
		bool revertY = false;
		for (TThing* p : solidProps)
		{
			if (p == this) continue;
			if (IsIntersecting(p))
			{
				revertY = true;
			}
		}
		if (collideWithScreenEdges && (GetBound(TOP) < 0 || GetBound(BOTTOM) > Renderer->GetHeight()))
		{
			revertY = true;
		}
		if (revertY)
		{
			Position.y -= dy;
		}

		return revertX || revertY;
	}

	void TThing::Draw()
	{
		if (m_Visible)
		{
			Renderer->DrawSprite(m_Sprite, Position.x - m_SpriteCenter.x, Position.y - m_SpriteCenter.y);
		}
	}
}
