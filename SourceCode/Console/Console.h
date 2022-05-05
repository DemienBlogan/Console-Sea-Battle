#pragma once
#include <string>

class Console
{
public:
	static void ClearScreen();
	static void WaitForPressKey();
	static void SetUnicodeCodepage();
	static void WaitForMilliseconds(int milliseconds);
	static void HideCursor();
	static void DisableMaximizeButton();
	static void DisableScrollBars();
	static void SetTitle(const std::wstring& title);
	static void SetFont(const std::wstring& fontName, int fontSize);
	static void SetDimensions(int width, int height);
	static void GetDesktopDimensions(int& width, int& height);
	static void SetWindowPositionOnScreenCenter();
	static void SetCursorPosition(int x, int y);
	static void ResetCursorPosition();
};