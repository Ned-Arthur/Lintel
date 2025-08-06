#pragma once
#include <Lintel.h>

#include "Player.h"

#include <iostream>

class Horse : public Lintel::TThing
{
public:
	using Lintel::TThing::TThing;

	Player* p;

	void Setup()
	{
		spriteFilePath = "assets/horse.spt";
		pos = { 10.0f, 10.0f };
		spriteCenter = { 1, 1 };

		p = dynamic_cast<Player*>(renderer->getThingByName("Player"));
	}

	void LateSetup() override
	{
		
	}

	void Update()
	{
		pos.x = p->pos.x;
		pos.y = p->pos.y + 3;
	}
};