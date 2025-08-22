#include <Lintel.h>

#include "Things/Player.h"
#include "Things/Enemy.h"
#include "Things/Horse.h"
#include "Things/Bullet.h"

int main(int argc, char** argv)
{
	Lintel::TRen ren;
	ren.SetTitle("Sandbox Game");
	ren.SetBackgroundSprite("assets/grass.spt");

	// Create TThings
	// These will be rendered bottom-to-top
	ren.CreateThing<Horse>("MyHorse", { "horse" })->InitPosition({ 8, 5 });
	ren.CreateThing<Player>("Player", {"solid"});

	ren.CreateThing<Enemy>("E1", { "solid", "shootable" });

	CREATE_PROP(ren, "assets/medRock.spt", 60, 12);
	CREATE_PROP(ren, "assets/house.spt", 20, 6);
	CREATE_PROP(ren, "assets/house.spt", 27, 6);
	CREATE_PROP(ren, "assets/fence_vertical.spt", 20, 10);
	CREATE_PROP(ren, "assets/fence_vertical.spt", 33, 10);
	CREATE_PROP(ren, "assets/fence_horizontal.spt", 20, 14);

	Lintel::Application app;
	app.RegisterTRen(&ren);

	app.Run();
}

