#pragma once

#include "../TThing.h"

#define CREATE_PROP(ren, spriteFile, posX, posY) { \
	Lintel::TThing* prop = ren.CreateThing<Lintel::Prop>("", {"solid"}); \
	prop->InitSprite(spriteFile); \
	prop->InitPosition({posX, posY}); \
}

namespace Lintel {

	class Prop : public TThing
	{
	public:
		using TThing::TThing;

		void Setup()
		{}

		void Update()
		{}
	};
}
