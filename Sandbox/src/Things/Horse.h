#pragma once
#include <Lintel.h>

class Horse : public Lintel::TThing
{
public:
	using Lintel::TThing::TThing;

	Lintel::TThing* rider = nullptr;

	bool beingRidden = false;
	float speedBonus = 2.f;

	void Setup() override
	{
		InitSprite("assets/horse.spt");
		InitPosition({ 40.0f, 5.0f });
		
		InitSpriteCenter({ 1, 1 });
	}

	void Update()
	{
		if (rider)
		{
			Position.x = rider->Position.x;
			Position.y = rider->Position.y + 1;
		}
	}

	void Ride(TThing* _p)
	{
		rider = _p;
	}

	void UnRide()
	{
		rider = nullptr;
	}
};