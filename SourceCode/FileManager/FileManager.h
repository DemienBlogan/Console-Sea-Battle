#pragma once
#include <string>
#include <map>
#include "../Game/GameEnumerations.h"

struct File
{
	std::wstring name;
	std::wstring content;

	File() = default;

	File(const std::wstring& name, const std::wstring& content = L"")
		: name(name), content(content)
	{ }
};

class FileManager
{
private:
	std::map<Menu, File> menus =
	{
		{ Menu::Credits, File(L"Resources/Credits/Credits.txt") },
		{ Menu::Audio, File(L"Resources/Menus/AudioMenu.txt") },
		{ Menu::ColorThemes, File(L"Resources/Menus/ColorThemesMenu.txt") },
		{ Menu::Difficulties, File(L"Resources/Menus/DifficultiesMenu.txt") },
		{ Menu::Main, File(L"Resources/Menus/MainMenu.txt") },
		{ Menu::Options, File(L"Resources/Menus/OptionsMenu.txt") },
	};

	std::map<Logo, File> logos =
	{
		{ Logo::Company, File(L"Resources/StartScreen/CompanyLogo.txt") },
		{ Logo::Game, File(L"Resources/StartScreen/GameLogo.txt") },
	};

	std::map<int, File> tutorialPages =
	{
		{ 0, File(L"Resources/Tutorial/TutorialPage1.txt") },
		{ 1, File(L"Resources/Tutorial/TutorialPage2.txt") },
		{ 2, File(L"Resources/Tutorial/TutorialPage3.txt") }
	};

	FileManager() = default;
	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;

public:
	static FileManager& GetInstance();

	void Initialize();
	std::wstring& GetMenuContent(Menu menu);
	std::wstring& GetLogoContent(Logo logo);
	std::wstring& GetTutorialContent(int page);

	bool ReadTextFromFile(const std::wstring& fileName, std::wstring& outputText);
	bool ReadIntFromFile(const std::wstring& fileName, int& outputNumber);
	bool WriteIntToFile(const std::wstring& fileName, int inputNumber);
};