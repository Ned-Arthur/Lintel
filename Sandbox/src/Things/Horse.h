#pragma once
#include <Lintel.h>

class Horse : public Lintel::TThing
{
public:
	using Lintel::TThing::TThing;

	Lintel::TThing* rider = nullptr;

	bool beingRidden = false;
	float speedBonus = 2.f;

	void Setup()
	{
		spriteFilePath = "assets/horse.spt";
		initPos({ 40.0f, 5.0f });
		
		spriteCenter = { 1, 1 };
	}

	void Update()
	{
		if (rider)
		{
			pos.x = rider->pos.x;
			pos.y = rider->pos.y + 1;
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