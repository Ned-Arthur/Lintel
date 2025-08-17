#pragma once

#include <Lintel.h>

#include "Enemy.h"

class Bullet : public Lintel::TThing
{
public:
	using Lintel::TThing::TThing;

	float speed = 30.0f;
	int xDir = 0;
	int yDir = 0;


	void Setup() override
	{
		spriteCenter = { 0, 0 };

		// idk why this works. I can't find a proper ascii table for this encoding...?
		Sprite()->setSpriteFromString("\x7", 1, 1, Lintel::RED, Lintel::TRANSPARENT);
	}

	void Update() override
	{
		pos.x += xDir * speed * Lintel::Time::deltaTime;
		pos.y += yDir * speed * Lintel::Time::deltaTime;

		std::vector<TThing*> walls = renderer->getThingsWithTag("solid");

		for (TThing* thing : walls)
		{
			if (isIntersecting(thing))
			{
				if (thing->tags.contains("shootable"))
				{
					Enemy* e = dynamic_cast<Enemy*>(thing);
					e->Hit(1);
				}
				
				QueueDelete();
				return;
			}
		}

		// Give up if we get too far away from the screen
		if (abs(pos.x) > 300 || abs(pos.y) > 300)
		{
			QueueDelete();
			return;
		}
	}

	// Initialise position and direction when instantiated by the player
	void init(TVec<float> pPos, int direction)
	{
		// 321
		// 4 0
		// 567
		
		switch (direction)
		{
		case 0:
			xDir = 1;
			yDir = 0;
			break;
		case 1:
			xDir = 1;
			yDir = -1;
			break;
		case 2:
			xDir = 0;
			yDir = -1;
			break;
		case 3:
			xDir = -1;
			yDir = -1;
			break;
		case 4:
			xDir = -1;
			yDir = 0;
			break;
		case 5:
			xDir = -1;
			yDir = 1;
			break;
		case 6:
			xDir = 0;
			yDir = 1;
			break;
		case 7:
			xDir = 1;
			yDir = 1;
			break;
		}
		pos = { pPos.x + 2 * xDir, pPos.y + 2 * yDir };
	}
};
