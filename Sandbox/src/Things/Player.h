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
		InitSprite("assets/human.spt");
		InitPosition({ 5.0f, 2.0f });
		InitSpriteCenter({ 1, 1 });
	}

	void Update() override
	{
		if (Lintel::Input::GetKeyState(Lintel::K_ESCAPE).IsHeld)
		{
			Renderer->QuitApp();
		}
		
		if (Lintel::Input::GetKeyState('F').JustPressed)
		{
			if (!currentMount)
			{
				std::vector<TThing*> horses = Renderer->GetThingsWithTag("horse");
				for (TThing* h : horses)
				{
					Horse* horse = dynamic_cast<Horse*>(h);
					if (IsIntersecting(horse))
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

		if (Lintel::Input::GetKeyState('A').IsHeld)
		{
			dx -= (speed * Lintel::Time::DeltaTime);
		}
		if (Lintel::Input::GetKeyState('D').IsHeld)
		{
			dx += (speed * Lintel::Time::DeltaTime);
		}
		if (Lintel::Input::GetKeyState('W').IsHeld)
		{
			dy -= (speed * Lintel::Time::DeltaTime);
		}
		if (Lintel::Input::GetKeyState('S').IsHeld)
		{
			dy += (speed * Lintel::Time::DeltaTime);
		}

		MoveByAndCollideWith(dx, dy, "solid", true);

		int w = Renderer->GetWidth();
		int h = Renderer->GetHeight();
		if (Position.x > w) Position.x -= w + 1;
		if (Position.y > h) Position.y -= h + 1;
		if (Position.x < -1) Position.x += w + 1;
		if (Position.y < -1) Position.y += h + 1;

		// Shooting
		Lintel::KeyState north = Lintel::Input::GetKeyState('I');
		Lintel::KeyState south = Lintel::Input::GetKeyState('K');
		Lintel::KeyState east  = Lintel::Input::GetKeyState('L');
		Lintel::KeyState west  = Lintel::Input::GetKeyState('J');

		int dir = -1;
		if (east.JustPressed)
		{
			if (north.IsHeld)
				dir = 1;
			else if (south.IsHeld)
				dir = 7;
			else
				dir = 0;
		}
		if (north.JustPressed)
		{
			if (east.IsHeld)
				dir = 1;
			else if (west.IsHeld)
				dir = 3;
			else
				dir = 2;
		}
		if (west.JustPressed)
		{
			if (north.IsHeld)
				dir = 3;
			else if (south.IsHeld)
				dir = 5;
			else
				dir = 4;
		}
		if (south.JustPressed)
		{
			if (west.IsHeld)
				dir = 5;
			else if (east.IsHeld)
				dir = 7;
			else
				dir = 6;
		}

		if (dir != -1)
		{
			Renderer->CreateThing<Bullet>()->init(Position, dir);
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
