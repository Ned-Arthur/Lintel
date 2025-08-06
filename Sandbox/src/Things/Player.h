#pragma once

#include <Lintel.h>

#include <iostream>

class Player : public Lintel::TThing
{
public:
	using Lintel::TThing::TThing;	// Unfortunately this boilerplate is required for it to work :(

	float speed = 10.0f;

	void Setup() override
	{
		spriteFilePath = "assets/demo.spt";
		pos = { 20.0f, 10.0f };
		spriteCenter = { 1, 1 };

		name;
	}

	void Update() override
	{
		if (Lintel::Input::getKeyState('A').currentState)
		{
			pos.x -= (speed * Lintel::Time::deltaTime);
		}
		if (Lintel::Input::getKeyState('D').currentState)
		{
			pos.x += (speed * Lintel::Time::deltaTime);
		}
		if (Lintel::Input::getKeyState('W').currentState)
		{
			pos.y -= (speed * Lintel::Time::deltaTime);
		}
		if (Lintel::Input::getKeyState('S').currentState)
		{
			pos.y += (speed * Lintel::Time::deltaTime);
		}

		int w = renderer->getWidth();
		int h = renderer->getHeight();

		if (pos.x > w) pos.x -= w + 1;
		if (pos.y > h) pos.y -= h + 1;
		if (pos.x < -1) pos.x += w + 1;
		if (pos.y < -1) pos.y += h + 1;
	}
};
