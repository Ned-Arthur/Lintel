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

	char txtbuf[30];
	float maxfps = 0;

	void Update() override
	{
		float fps = 1 / Lintel::Time::deltaTime;
		if (fps > maxfps) maxfps = fps;
		sprintf(txtbuf, "FPS: %4.4f", fps);
		renderer->drawMsg(txtbuf, Lintel::BLACK, Lintel::GREEN, 60, 2);
		sprintf(txtbuf, "Max FPS: %4.4f", maxfps);
		renderer->drawMsg(txtbuf, Lintel::BLACK, Lintel::GREEN, 60, 3);
		
		if (Lintel::Input::getKeyState(Lintel::K_ESCAPE).currentState)
			renderer->QuitApp();
		
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
