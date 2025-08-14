#include "Input.h"

#include <cctype>

namespace Lintel {
	// Create the static members
	std::unordered_map<Key, KeyState> Input::keyData;
	std::unordered_map<char, KeyState> Input::letterData;
	
	void Input::setKeyState(Key key, bool newState)
	{
		if (keyData[key].currentState == false && newState == true)
			keyData[key].justPressed = true;

		keyData[key].currentState = newState;
	}
	void Input::setKeyState(char letter, bool newState)
	{
		letter = toupper(letter);

		if (letterData[letter].currentState == false && newState == true)
			letterData[letter].justPressed = true;

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

	void Input::Update()
	{
		// Update the state of justPressed the frame after it's set
		
		for (auto k = keyData.begin(); k != keyData.end(); ++k)
		{
			if (k->second.justPressed == true)
			{
				k->second.justPressed = false;
			}
		}

		for (auto l = letterData.begin(); l != letterData.end(); ++l)
		{
			if (l->second.justPressed == true)
			{
				l->second.justPressed = false;
			}
		}
	}
}