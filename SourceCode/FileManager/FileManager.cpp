#include "FileManager.h"
#include <fstream>
#include <iterator>
#include "../Debug/Debug.h"

FileManager& FileManager::GetInstance()
{
	static FileManager fileManager;
	return fileManager;
}

void FileManager::Initialize()
{
	bool success;

	for (auto& file : menus)
	{
		success = ReadTextFromFile(file.second.name, file.second.content);
		CHECK_EXPRESSION(success);
	}

	for (auto& file : logos)
	{
		success = ReadTextFromFile(file.second.name, file.second.content);
		CHECK_EXPRESSION(success);
	}

	for (auto& file : tutorialPages)
	{
		success = ReadTextFromFile(file.second.name, file.second.content);
		CHECK_EXPRESSION(success);
	}
}

std::wstring& FileManager::GetMenuContent(Menu menu)
{
	return menus[menu].content;
}

std::wstring& FileManager::GetLogoContent(Logo logo)
{
	return logos[logo].content;
}

std::wstring& FileManager::GetTutorialContent(int page)
{
	return tutorialPages[page].content;
}


bool FileManager::ReadTextFromFile(const std::wstring& fileName, std::wstring& outputText)
{
	std::wifstream fileStream(fileName);
	if (!fileStream.is_open())
		return false;

	outputText.assign((std::istreambuf_iterator<wchar_t>(fileStream)), {});

	if (fileStream.fail())
		return false;

	fileStream.close();

	return true;
}

bool FileManager::ReadIntFromFile(const std::wstring& fileName, int& outputNumber)
{
	std::wifstream fileStream(fileName);
	if (!fileStream.is_open())
		return false;

	fileStream >> outputNumber;
	
	if (fileStream.fail())
		return false;

	fileStream.close();

	return true;
}

bool FileManager::WriteIntToFile(const std::wstring& fileName, int inputNumber)
{
	std::wofstream fileStream(fileName);
	if (!fileStream.is_open())
		return false;

	fileStream << inputNumber;

	if (fileStream.fail())
		return false;

	fileStream.close();

	return true;
}