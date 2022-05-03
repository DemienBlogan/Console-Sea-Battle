#include "FileManager.h"
#include <fstream>
#include <iterator>
#include "../Game/Game.h"

std::wstring FileManager::ReadTextFile(const std::wstring& fileName)
{
	std::wifstream fileStream(fileName);
	if (!fileStream.is_open())
	{
		throw Game::Exception(L"File '" + fileName + L"' could not been opened", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	std::wstring content((std::istreambuf_iterator<wchar_t>(fileStream)), {});

	return content;
}