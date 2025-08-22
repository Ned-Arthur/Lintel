#pragma once

#include "Application.h"

#include "lnpch.h"

// Each renderer implementation needs to have its header included here and the
// function to set input added as a friend

namespace Lintel {
	class TRen;

	enum Key {
		K_ESCAPE
	};
	
	struct KeyState {
		bool IsHeld;
		bool JustPressed;
	};
	
	class Input
	{
	public:
		static KeyState GetKeyState(Key key);
		static KeyState GetKeyState(char key);

	private:
		static void Update();
		static void SetKeyState(Key key, bool newState);
		static void SetKeyState(char letter, bool newState);
		
		static std::unordered_map<Key, KeyState> m_KeyData;
		static std::unordered_map<char, KeyState> m_LetterData;

		friend void Application::Run();
		friend TRen;
	};

}

