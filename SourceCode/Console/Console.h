#pragma once

class Console
{
public:
	static void ClearScreen();
	static void WaitForPressKey();
	static void SetUnicodeCodepage();
	static void WaitForMilliseconds(int milliseconds);
};