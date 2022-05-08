#include "Input.h"
#include <conio.h>

Input::Key Input::pressedKey = Input::Key::None;

bool Input::PressKey()
{
	// Function '_kbhit' returns true, is user press any key.
	return _kbhit();
}

Input::Key Input::GetPressedKey()
{
	// Function '_getch' returns windows-code of the key that user
	// pressed. But if user pressed any arrow, function returns 2 codes:
	// first is arrow code, and second is arrow direction.
	pressedKey = static_cast<Key>(_getch());
	if (pressedKey == Key::Arrow)
	{
		pressedKey = static_cast<Key>(_getch());
	}

	return pressedKey;
}