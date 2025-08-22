#include "Input.h"

#include <cctype>

namespace Lintel {
	// Create the static members
	std::unordered_map<Key, KeyState> Input::m_KeyData;
	std::unordered_map<char, KeyState> Input::m_LetterData;
	
	void Input::SetKeyState(Key key, bool newState)
	{
		if (m_KeyData[key].IsHeld == false && newState == true)
			m_KeyData[key].JustPressed = true;

		m_KeyData[key].IsHeld = newState;
	}
	void Input::SetKeyState(char letter, bool newState)
	{
		letter = toupper(letter);

		if (m_LetterData[letter].IsHeld == false && newState == true)
			m_LetterData[letter].JustPressed = true;

		m_LetterData[letter].IsHeld = newState;
	}

	KeyState Input::GetKeyState(Key key)
	{
		return m_KeyData[key];
	}
	KeyState Input::GetKeyState(char key)
	{
		return m_LetterData[key];
	}

	void Input::Update()
	{
		// Update the state of justPressed the frame after it's set
		
		for (auto keyDataEntry = m_KeyData.begin(); keyDataEntry != m_KeyData.end(); ++keyDataEntry)
		{
			if (keyDataEntry->second.JustPressed == true)
			{
				keyDataEntry->second.JustPressed = false;
			}
		}

		for (auto letterDataEntry = m_LetterData.begin(); letterDataEntry != m_LetterData.end(); ++letterDataEntry)
		{
			if (letterDataEntry->second.JustPressed == true)
			{
				letterDataEntry->second.JustPressed = false;
			}
		}
	}
}
