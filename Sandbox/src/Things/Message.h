#pragma once
#include <Lintel.h>

class Message : public Lintel::TThing
{
public:
	using Lintel::TThing::TThing;

	float dieTime;

	void Setup() override
	{
		SetVisibility(false);
		dieTime = Lintel::Time::ClockTime + 1.f;
	}

	void Update()
	{
		if (Lintel::Time::ClockTime > dieTime)
		{
			QueueDelete();
		}

		Renderer->DrawString("Pow!", Lintel::CYAN, Lintel::BLACK, 2, 5);
	}
};