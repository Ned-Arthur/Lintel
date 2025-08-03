#pragma once

#include <unordered_map>

namespace Lintel {
	enum Key {
		K_ESCAPE
	};
	
	struct KeyState {
		bool prevState;
		bool currentState;
	};
	
	class Input
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

