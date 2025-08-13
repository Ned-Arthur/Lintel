#include <Lintel.h>

#include "Things/Player.h"
#include "Things/Horse.h"

int main(int argc, char** argv)
{
	Lintel::TRen ren;
	ren.setTitle("Sandbox Game");
	ren.setBGSprite("assets/grass.spt");

	// Create TThings
	// These will be rendered bottom-to-top
	ren.createThing<Horse>("Horse");
	ren.createThing<Player>("Player");

	Lintel::Application app;
	app.registerTRen(&ren);

	app.Run();
}

