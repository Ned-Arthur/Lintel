#include <Lintel.h>

#include "Things/Player.h"
#include "Things/Horse.h"

class Sandbox : public Lintel::Application
{
public:
	Lintel::TRen ren;

	void Setup() override
	{
		ren.setTitle("Sandbox Game");
		ren.setBGSprite("assets/grass.spt");

		// Create Things
		// These will be rendered bottom-to-top
		ren.createThing<Horse>("Horse");
		ren.createThing<Player>("Player");

		ren.setupThings();
	}

	void Update() override
	{
		ren.update();	// Deal with events (keypress, resize)
		
		if (Lintel::Input::getKeyState(Lintel::K_ESCAPE).currentState) Quit();

		ren.redraw();
	}
};

Lintel::Application* Lintel::CreateApplication()
{
	return new Sandbox();
}
