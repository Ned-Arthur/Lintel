#pragma once

#include <Lintel.h>
#include <iostream>

#include "Message.h"

#define BUFFERLENGTH 10

struct InputBuffer
{
	// Members
	char Queue[BUFFERLENGTH+1];
	int WriteLocation = 0;
	int ReadLocation = 0;

	InputBuffer()	// Constructor
	{
		// Fill the buffer with 'blank' entries
		for (int i = 0; i < BUFFERLENGTH; i++) Queue[i] = '_';
		Queue[BUFFERLENGTH] = '\0';	// Null termination for easy display
	}

	// Push an input to the back of the queue
	void Push(char input)
	{
		Queue[WriteLocation] = input;
		WriteLocation++;
		WriteLocation %= BUFFERLENGTH;
	}

	// Fetch and consume an input from the front of the queue
	char DeQueue()
	{
		if (ReadLocation == WriteLocation)
		{
			// There's no input to be read
			return '\0';
		}
		
		char value = Queue[ReadLocation];
		Queue[ReadLocation] = '_';
		ReadLocation++;
		ReadLocation %= BUFFERLENGTH;	// Wrap around

		return value;
	}

	// Peek ahead in the queue without consuming the input
	char Peek(int offset)
	{
		return Queue[(ReadLocation + offset) % BUFFERLENGTH];
	}
};


class Player : public Lintel::TThing
{
public:
	using Lintel::TThing::TThing;
	float speed = 10.0f;


	void Setup() override
	{
		InitSprite("assets/human.spt");
		InitPosition({ 5.0f, 10.0f });
		InitSpriteCenter({ 1, 1 });
	}

	InputBuffer input;

	void Update() override
	{

		// Buffer inputs
		if (Lintel::Input::GetKeyState('W').JustPressed) input.Push('W');
		if (Lintel::Input::GetKeyState('A').JustPressed) input.Push('A');
		if (Lintel::Input::GetKeyState('S').JustPressed) input.Push('S');
		if (Lintel::Input::GetKeyState('D').JustPressed) input.Push('D');

		// Show buffer
		int bufStartX = 2, bufStartY = 2;
		Renderer->DrawCharacter(Lintel::TChar('v', Lintel::RED, Lintel::BLACK), bufStartX + input.WriteLocation, bufStartY-1);
		Renderer->DrawCharacter(Lintel::TChar('^', Lintel::GREEN, Lintel::BLACK), bufStartX + input.ReadLocation, bufStartY + 1);
		Renderer->DrawString(input.Queue, Lintel::WHITE, Lintel::BLACK, bufStartX, bufStartY);

		// Process buffered inputs - Wait for a keypress for easy observation
		if (Lintel::Input::GetKeyState('R').JustPressed)
		{
			char next = input.DeQueue();

			
			switch (next)
			{
			case 'A':
				// Might be a motion
				// Check the rest of the motion sequence
				if (input.Peek(0) == 'S' && input.Peek(1) == 'D')
				{
					// Consume those inputs
					input.DeQueue(); input.DeQueue();
					// Perform the action
					Renderer->CreateThing<Message>();
				}
			}
		}

		// ... Rest of file ...

		if (Lintel::Input::GetKeyState(Lintel::K_ESCAPE).IsHeld)
		{
			Renderer->QuitApp();
		}

		// Movement
		/*
		float dx = 0, dy = 0;

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
		*/
	}
};
