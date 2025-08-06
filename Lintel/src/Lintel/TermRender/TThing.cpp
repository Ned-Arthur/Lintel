#include "TThing.h"

#include "TRen.h"

namespace Lintel {
	TThing::TThing(TRen* _renderer, std::string _name)
		: renderer(_renderer), name(_name)
	{}

	void TThing::genericSetup()
	{
		Setup();

		sprite.loadSprite(spriteFilePath);
	}

	void TThing::Draw()
	{
		if (visible)
		{
			renderer->drawSprite(sprite, pos.x - spriteCenter.x, pos.y - spriteCenter.y);
		}
	}
}
