#pragma once

#include "Core.h"

#include <unordered_map>

namespace Lintel {
	enum Key {
		K_COMMA,
		K_FULLSTOP,
		K_FSLASH,
		K_BSLASH,

		K_APOSTROPHE,
		K_LBRACKET,
		K_RBRACKET,
		K_DASH,

		K_BACKTICK,
		K_ESCAPE
	};
	
	struct KeyState {
		bool prevState;
		bool currentState;
	};
	
	class LINTEL_API Input
	{
	public:
		static void setKeyState(Key key, bool newState);
		static void setKeyState(char letter, bool newState);
		static KeyState getKeyState(Key key);
		static KeyState getKeyState(char key);

	private:
		static std::unordered_map<Key, KeyState> keyData;
		static std::unordered_map<char, KeyState> letterData;
	};

}

