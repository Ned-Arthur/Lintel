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
	ren.createThing<Player>("Player");
	ren.createThing<Horse>("MyHorse");
	ren.createThing<Horse>("OtherHorse")->initPos(TVec{ 10.f, 25.f });

	Lintel::Application app;
	app.registerTRen(&ren);

	app.Run();
}

