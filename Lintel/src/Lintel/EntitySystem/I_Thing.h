#pragma once

#include <string>

namespace Lintel {

	class I_Thing
	{
	public:
		I_Thing(std::string _name) : name(_name) {}

		/* Overridable functions for app - space control */
		// Engine-called setup, override to create graphics assets for each Thing
		// implementation.
		virtual void genericSetup() = 0;
		// Set members, and get references to other things
		// Named things exist here, but aren't guaranteed to have values
		virtual void Setup() = 0;
		// Optional setup based on values from other Things. All Setup has been
		// completed when this is called
		virtual void LateSetup() {}

		// Called every frame, take input and do movement
		virtual void Update() = 0;

	/* Pseudo-protected members, but need to access from other Things for game logic */
		std::string name;		// Identification
		bool visible = true;	// Do we render this Thing

		void Render();
	};

}
