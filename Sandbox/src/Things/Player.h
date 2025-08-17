#pragma once

#include <Lintel.h>

#include "Horse.h"
#include "Bullet.h"

#include <iostream>

class Horse;

class Player : public Lintel::TThing
{
public:
	using Lintel::TThing::TThing;

	int health = 4;

	float speed = 10.0f;
	Horse* currentMount = nullptr;

	void Setup() override
	{
		spriteFilePath = "assets/human.spt";
		initPos({ 5.0f, 2.0f });
		spriteCenter = { 1, 1 };
	}

	void Update() override
	{
		if (Lintel::Input::getKeyState(Lintel::K_ESCAPE).currentState)
		{
			renderer->QuitApp();
		}
		
		if (Lintel::Input::getKeyState('F').justPressed)
		{
			if (!currentMount)
			{
				std::vector<TThing*> horses = renderer->getThingsWithTag("horse");
				for (TThing* h : horses)
				{
					Horse* horse = dynamic_cast<Horse*>(h);
					if (isIntersecting(horse))
					{
						horse->Ride(this);
						currentMount = horse;
						speed *= currentMount->speedBonus;
						return;
					}
				}
			}
			else
			{
				speed /= currentMount->speedBonus;
				currentMount->UnRide();
				currentMount = nullptr;
			}
		}

		// Movement
		float dx=0, dy=0;

		if (Lintel::Input::getKeyState('A').currentState)
		{
			dx -= (speed * Lintel::Time::deltaTime);
		}
		if (Lintel::Input::getKeyState('D').currentState)
		{
			dx += (speed * Lintel::Time::deltaTime);
		}
		if (Lintel::Input::getKeyState('W').currentState)
		{
			dy -= (speed * Lintel::Time::deltaTime);
		}
		if (Lintel::Input::getKeyState('S').currentState)
		{
			dy += (speed * Lintel::Time::deltaTime);
		}

		moveByAndCollideWith(dx, dy, "solid", true);

		int w = renderer->getWidth();
		int h = renderer->getHeight();
		if (pos.x > w) pos.x -= w + 1;
		if (pos.y > h) pos.y -= h + 1;
		if (pos.x < -1) pos.x += w + 1;
		if (pos.y < -1) pos.y += h + 1;

		// Shooting
		Lintel::KeyState north = Lintel::Input::getKeyState('I');
		Lintel::KeyState south = Lintel::Input::getKeyState('K');
		Lintel::KeyState east  = Lintel::Input::getKeyState('L');
		Lintel::KeyState west  = Lintel::Input::getKeyState('J');

		int dir = -1;
		if (east.justPressed)
		{
			if (north.currentState)
				dir = 1;
			else if (south.currentState)
				dir = 7;
			else
				dir = 0;
		}
		if (north.justPressed)
		{
			if (east.currentState)
				dir = 1;
			else if (west.currentState)
				dir = 3;
			else
				dir = 2;
		}
		if (west.justPressed)
		{
			if (north.currentState)
				dir = 3;
			else if (south.currentState)
				dir = 5;
			else
				dir = 4;
		}
		if (south.justPressed)
		{
			if (west.currentState)
				dir = 5;
			else if (east.currentState)
				dir = 7;
			else
				dir = 6;
		}

		if (dir != -1)
		{
			renderer->createThing<Bullet>()->init(pos, dir);
		}
	}

	void Hit(int damage)
	{
		health -= damage;

		if (health <= 0)
		{
			// Player died, close game
			exit(1);
		}
	}
};
