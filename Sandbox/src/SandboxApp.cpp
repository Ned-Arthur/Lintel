#include <Lintel.h>

#include "Things/Player.h"
#include "Things/Enemy.h"
#include "Things/Message.h"
#include "Things/Bullet.h"

int main(int argc, char** argv)
{
	Lintel::TRen ren;
	ren.SetTitle("Sandbox Game");
	//ren.SetBackgroundSprite("assets/grass.spt");
	ren.SetBackgroundCharacter(Lintel::TChar(' '));

	// Create TThings
	// These will be rendered bottom-to-top
	ren.CreateThing<Player>("Player", {"solid"});


	Lintel::Application app;
	app.RegisterTRen(&ren);

	app.Run();
}

