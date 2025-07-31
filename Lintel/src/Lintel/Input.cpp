#include "Input.h"

#include <cctype>

namespace Lintel {
	std::unordered_map<Key, KeyState> Input::keyData;
	std::unordered_map<char, KeyState> Input::letterData;
	
	void Input::setKeyState(Key key, bool newState)
	{
		keyData[key].prevState = keyData[key].currentState;
		keyData[key].currentState = newState;
	}
	void Input::setKeyState(char letter, bool newState)
	{
		/*
		Key processedKey = (Key)(K_a + (tolower(letter) - 'a'));	// We ball
		//if (processedKey < 0 || processedKey > K_z) return;	// Ball a little less
		setKeyState(processedKey, newState);
		*/
		letter = toupper(letter);
		letterData[letter].prevState = letterData[letter].currentState;
		letterData[letter].currentState = newState;
	}

	KeyState Input::getKeyState(Key key)
	{
		return keyData[key];
	}
	KeyState Input::getKeyState(char key)
	{
		return letterData[key];
	}
}