#include "TThing.h"

#include "TRen.h"

namespace Lintel {
	TThing::TThing(TRen* _renderer, std::string _name, std::unordered_set<std::string> _tags)
		: renderer(_renderer), name(_name), tags(_tags)
	{}

	void TThing::genericSetup()
	{
		Setup();

		if (spriteFilePath != "NONE")
		{
			sprite.loadSprite(spriteFilePath);
		}
	}

	void TThing::initPos(TVec<float> startPos)
	{
		if (!posInitialised)
		{
			pos = startPos;
			posInitialised = true;
		}
	}

	void TThing::initSpriteFP(const char* filePath)
	{
		if (!spriteInitialised)
		{
			spriteFilePath = filePath;
			spriteInitialised = true;
		}
	}

	void TThing::QueueDelete()
	{
		shouldDelete = true;
	}

	bool TThing::MarkedForDeletion()
	{
		return shouldDelete;
	}

	// Basic rectangle intersection
	bool TThing::isIntersecting(TThing* other)
	{
		int totalSpriteWidth = getBound(RIGHT) - getBound(LEFT) + other->getBound(RIGHT) - other->getBound(LEFT);
		int totalSpriteHeight = getBound(BOTTOM) - getBound(TOP) + other->getBound(BOTTOM) - other->getBound(TOP);

		

		int topMostChar = min(getBound(TOP), other->getBound(TOP));
		int bottomMostChar = max(getBound(BOTTOM), other->getBound(BOTTOM));
		int boundingRectHeight = bottomMostChar - topMostChar;

		int leftMostChar = min(getBound(LEFT), other->getBound(LEFT));
		int rightMostChar = max(getBound(RIGHT), other->getBound(RIGHT));
		int boundingRectWidth = rightMostChar - leftMostChar;

		if (boundingRectHeight < totalSpriteHeight && boundingRectWidth < totalSpriteWidth)
		{
			return true;
		}
		return false;
	}

	int TThing::getBound(EdgeDirection dir)
	{
		switch (dir)
		{
		case LEFT:
			return pos.x - spriteCenter.x;
		case RIGHT:
			return pos.x - spriteCenter.x + sprite.getWidth();
		case TOP:
			return pos.y - spriteCenter.y;
		case BOTTOM:
			return pos.y - spriteCenter.y + sprite.getHeight();
		}
		
		return -1;
	}

	// Move by (dx, dy), colliding with / sliding along TThings with `solidTag` (and optionally screen edges)
	// Returns whether a collision occured
	bool TThing::moveByAndCollideWith(float dx, float dy, std::string solidTag, bool collideWithScreenEdges)
	{
		std::vector<TThing*> solidProps = renderer->getThingsWithTag("solid");
		
		pos.x += dx;
		bool revertX = false;
		for (TThing* p : solidProps)
		{
			if (p == this) continue;
			if (isIntersecting(p))
			{
				revertX = true;
			}
		}
		if (collideWithScreenEdges && (getBound(LEFT) < 0 || getBound(RIGHT) > renderer->getWidth()))
		{
			revertX = true;
		}
		if (revertX)
		{
			pos.x -= dx;
		}

		pos.y += dy;
		bool revertY = false;
		for (TThing* p : solidProps)
		{
			if (p == this) continue;
			if (isIntersecting(p))
			{
				revertY = true;
			}
		}
		if (collideWithScreenEdges && (getBound(TOP) < 0 || getBound(BOTTOM) > renderer->getHeight()))
		{
			revertY = true;
		}
		if (revertY)
		{
			pos.y -= dy;
		}

		return revertX || revertY;
	}

	TSprite* TThing::Sprite()
	{
		return &sprite;
	}

	void TThing::Draw()
	{
		if (visible)
		{
			renderer->drawSprite(sprite, pos.x - spriteCenter.x, pos.y - spriteCenter.y);
		}
	}
}
