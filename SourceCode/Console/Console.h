#pragma once
#include <string>

class Console
{
public:
	enum class Color : char
	{
		Blue = '1',
		Green = '2',
		Aqua = '3',
		Red = '4',
		Purple = '5',
		Yellow = '6',
		White = '7',
		Gray = '8',
		LightBlue = '9',
		Black = '0',
		LightGreen = 'A',
		LightAqua = 'B',
		LightRed = 'C',
		LightPurple = 'D',
		LightYellow = 'E',
		BrightWhite = 'F'
	};

private:
	static Color fontColor;
	static Color backgroundColor;

	static void SetConsoleColor();

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
	static void SetFontColor(Color color);
	static void SetBackgroundColor(Color color);
};