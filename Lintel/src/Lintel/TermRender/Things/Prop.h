#pragma once

#include "../TThing.h"

#define CREATE_PROP(ren, spriteFile, posX, posY) { \
	Lintel::TThing* prop = ren.createThing<Lintel::Prop>("", {"solid"}); \
	prop->initSpriteFP(spriteFile); \
	prop->initPos({posX, posY}); \
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
