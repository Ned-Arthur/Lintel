#pragma once
#include <Lintel.h>

#include "Player.h"

#include <iostream>

class Horse : public Lintel::TThing
{
public:
	using Lintel::TThing::TThing;

	Player* p;

	bool beingRidden = false;
	float speedBonus = 2.f;

	void Setup()
	{
		spriteFilePath = "assets/horse.spt";
		initPos({ 40.0f, 10.0f });
		
		spriteCenter = { 1, 1 };

		p = dynamic_cast<Player*>(renderer->getThingByName("Player"));
	}

	void Update()
	{
		if (beingRidden)
		{
			pos.x = p->pos.x;
			pos.y = p->pos.y + 1;
		}

		if (Lintel::Input::getKeyState('F').justPressed &&
			pos.dxTo(p->pos) < 4 && pos.dyTo(p->pos) < 3)
		{
			if (!beingRidden)
			{
				p->speed *= speedBonus;
				beingRidden = true;
			}
			else
			{
				p->speed /= speedBonus;
				beingRidden = false;
			}
		}

		if (Lintel::Input::getKeyState('K').justPressed)
		{
			// Kill this horse
		}
	}
};