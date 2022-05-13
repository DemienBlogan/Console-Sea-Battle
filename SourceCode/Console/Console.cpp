#include "Console.h"
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <io.h>
#include <thread>
#include <Windows.h>
#include <iostream>

Console::Color Console::fontColor = Console::Color::White;
Console::Color Console::backgroundColor = Console::Color::Black;

void Console::SetConsoleColor()
{
	// This method uses 'system' function.
	// Function 'system' gets c-string.
	// To change console color, we need to send c-string "Color XX",
	// where XX is two OCT digits. First is background color, and
	// second is text color. So I build c-string first, and then 
	// invoke 'system' function
	char colorRepresentation[9] = "Color ";
	colorRepresentation[6] = static_cast<char>(backgroundColor);
	colorRepresentation[7] = static_cast<char>(fontColor);
	system(colorRepresentation);
}

void Console::ClearScreen()
{
	system("cls");
}

void Console::WaitForPressKey()
{
	system("pause");
}

void Console::SetUnicodeCodepage()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
}

void Console::WaitForMilliseconds(int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Console::HideCursor()
{
	static HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100; // just some value. 0 won't work.
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleWindow, &cursorInfo);
}

void Console::DisableMaximizeButton()
{
	HWND consoleWindow = GetConsoleWindow();
	DWORD windowStyle = GetWindowLong(consoleWindow, GWL_STYLE);
	windowStyle &= ~WS_MAXIMIZEBOX;
	SetWindowLong(consoleWindow, GWL_STYLE, windowStyle);
	SetWindowPos(consoleWindow, nullptr, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

void Console::DisableScrollBars()
{
	HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(consoleWindow, &bufferInfo);

	COORD newBuffetSize =
	{
		bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1,
		bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1
	};

	SetConsoleScreenBufferSize(consoleWindow, newBuffetSize);
}

void Console::SetTitle(const std::wstring& title)
{
	SetConsoleTitle(title.c_str());
}

void Console::SetFont(const std::wstring& fontName, int fontSize)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = fontSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, fontName.length() + 1, fontName.c_str());

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
}

void Console::SetDimensions(int width, int height)
{
	SMALL_RECT windowArea = { 0, 0, static_cast<SHORT>(width), static_cast<SHORT>(height) };
	static HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(consoleWindow, true, &windowArea);
}

void Console::GetDesktopDimensions(int& width, int& height)
{
	RECT desktopRectangle;
	const HWND desktop = GetDesktopWindow();
	GetWindowRect(desktop, &desktopRectangle);
	width = desktopRectangle.right;
	height = desktopRectangle.bottom;
}

void Console::SetWindowPositionOnScreenCenter()
{
	// Get desktop dimensions:
	int desktopWidth, desktopHeight;
	GetDesktopDimensions(desktopWidth, desktopHeight);

	// Get console dimensions:
	HWND consoleWindow = GetConsoleWindow();
	RECT consoleRectangle;
	GetWindowRect(consoleWindow, &consoleRectangle);
	int consoleWidth = consoleRectangle.right - consoleRectangle.left;
	int consoleHeight = consoleRectangle.bottom - consoleRectangle.top;

	// Calculate console window new position;
	int centerPositionX = (desktopWidth / 2) - (consoleWidth / 2);
	int centerPositionY = (desktopHeight / 2) - (consoleHeight / 2);

	// Set console window position on screen center:
	SetWindowPos(consoleWindow, 0, centerPositionX, centerPositionY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Console::SetCursorPosition(int x, int y)
{
	static HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);
	std::wcout.flush();
	COORD newCursorPosition = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(consoleWindow, newCursorPosition);
}

void Console::ResetCursorPosition()
{
	SetCursorPosition(0, 0);
}

void Console::SetFontColor(Color color)
{
	fontColor = color;
	SetConsoleColor();
}

void Console::SetBackgroundColor(Color color)
{
	backgroundColor = color;
	SetConsoleColor();
}