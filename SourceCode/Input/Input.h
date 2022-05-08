#pragma once

class Input
{
public:
	enum class Key
	{
		// All numbers is OS Windows's codes of keys:
		Enter = 13,
		Escape = 27,
		ArrowUp = 72,
		ArrowLeft = 75,
		ArrowRight = 77,
		ArrowDown = 80,
		Arrow = 224,
		None = -1
	};

private:
	static Key pressedKey;

public:
	static bool PressKey();
	static Key GetPressedKey();
};