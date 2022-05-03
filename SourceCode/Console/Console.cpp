#include "Console.h"
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <io.h>
#include <thread>

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