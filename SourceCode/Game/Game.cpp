#include "Game.h"
#include <iostream>
#include <fstream>
#include "../Console/Console.h"
#include "../FileManager/FileManager.h"
#include "../Input/Input.h"

void Game::HandleInputMenu()
{
	switch (currentMenu)
	{
	case Game::Menu::Main:
		HandleInputMainMenu();
		break;

	case Game::Menu::Options:
		HandleInputOptionsMenu();
		break;

	case Game::Menu::Tutorial:
		HandleInputTutorialMenu();
		break;

	case Game::Menu::ColorThemes:
		HandleInputColorThemesMenu();
		break;

	case Game::Menu::MusicAndSounds:
		// TODO: Write code
		break;

	case Game::Menu::Credits:
		HandleInputCreditsMenu();
		break;

	case Game::Menu::Difficulties:
		HandleInputDifficultiesMenu();
		break;

	default:
		throw Exception(L"Variable 'currentMenu' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}
}

void Game::HandleInputMainMenu()
{
	if (Input::PressKey())
	{
		Input::Key pressedKey = Input::GetPressedKey();

		switch (pressedKey)
		{
		case Input::Key::ArrowUp:
			MoveMenuItemUp(selectedMainMenuItem, MainMenuItem::StartGame, MainMenuItem::Exit);
			break;

		case Input::Key::ArrowDown:
			MoveMenuItemDown(selectedMainMenuItem, MainMenuItem::StartGame, MainMenuItem::Exit);
			break;

		case Input::Key::Enter:
			switch (selectedMainMenuItem)
			{
			case Game::MainMenuItem::StartGame:
				currentMenu = Menu::Difficulties;
				break;

			case Game::MainMenuItem::Options:
				currentMenu = Menu::Options;
				break;

			case Game::MainMenuItem::Tutorial:
				currentMenu = Menu::Tutorial;
				break;

			case Game::MainMenuItem::Exit:
				isRunning = false;
				break;

			default:
				throw Exception(L"Variable 'selectedMainMenuItem' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
			}
			break;

		case Input::Key::Escape:
			isRunning = false;
			break;
		}
	}
}

void Game::UpdateMenu()
{
	switch (currentMenu)
	{
	case Game::Menu::Main:
		UpdateMainMenu();
		break;

	case Game::Menu::Options:
		UpdateOptionsMenu();
		break;

	case Game::Menu::Tutorial:
		// No code
		break;

	case Game::Menu::ColorThemes:
		UpdateColorThemesMenu();
		break;

	case Game::Menu::MusicAndSounds:
		break;

	case Game::Menu::Credits:
		// No code
		break;

	case Game::Menu::Difficulties:
		UpdateDifficultiesMenu();
		break;

	default:
		throw Exception(L"Variable 'currentMenu' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}
}

void Game::HandleInputTutorialMenu()
{
	if (Input::PressKey())
	{
		Input::Key pressedKey = Input::GetPressedKey();

		switch (pressedKey)
		{
		case Input::Key::ArrowLeft:
			if (currentPage > 0)
			{
				currentPage--;
			}
			break;

		case Input::Key::ArrowRight:
			if (currentPage < TUTORIAL_PAGES_COUNT - 1)
			{
				currentPage++;
			}
			break;

		case Input::Key::Escape:
			currentPage = 0;
			currentMenu = Menu::Main;
			break;
		}
	}
}

void Game::UpdateMainMenu()
{
	// --- REMOVING ARROW FROM PREVIOUS SELECTED ITEM ---
	size_t arrowPosition = mainMenuFileContent.find(L"->");
	if (arrowPosition != std::wstring::npos)
	{
		mainMenuFileContent[arrowPosition] = ' ';
		mainMenuFileContent[arrowPosition + 1] = ' ';
	}

	// --- SET ARROW ON NEW SELECTED ITEM ---
	// In the menu we need to only set arrow between '[" and ']' brackyes.
	// So algorithm will be next:

	// 1. Find selected menu item first character position in file content:
	size_t foundPosition;
	switch (selectedMainMenuItem)
	{
	case Game::MainMenuItem::StartGame:
		foundPosition = mainMenuFileContent.find(L"Start Game");
		break;

	case Game::MainMenuItem::Options:
		foundPosition = mainMenuFileContent.find(L"Options");
		break;

	case Game::MainMenuItem::Tutorial:
		foundPosition = mainMenuFileContent.find(L"Tutorial");
		break;

	case Game::MainMenuItem::Exit:
		foundPosition = mainMenuFileContent.find(L"Exit");
		break;

	default:		
		throw Exception(L"Variable 'selectedMainMenuItem' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	if (foundPosition == std::wstring::npos)
	{
		throw Exception(L"Variable 'foundPosition' == std::wstring::npos", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	// 2. Descrease its value by 4, because open '[' is on 4 characters left:
	foundPosition -= 4;

	// 3. Replace two whitespaces (' ') on characters '-' and '>':
	mainMenuFileContent[foundPosition] = '-';
	mainMenuFileContent[foundPosition + 1] = '>';
}

void Game::HandleInputCreditsMenu()
{
	if (Input::PressKey())
	{
		Input::Key pressedKey = Input::GetPressedKey();

		switch (pressedKey)
		{
		case Input::Key::Escape:
			currentMenu = Menu::Options;
			break;
		}
	}
}

void Game::HandleInputOptionsMenu()
{
	if (Input::PressKey())
	{
		Input::Key pressedKey = Input::GetPressedKey();

		switch (pressedKey)
		{
		case Input::Key::ArrowUp:
			MoveMenuItemUp(selectedOptionsMenuItem, OptionsMenuItem::ColorTheme, OptionsMenuItem::BackToMainMenu);
			break;

		case Input::Key::ArrowDown:
			MoveMenuItemDown(selectedOptionsMenuItem, OptionsMenuItem::ColorTheme, OptionsMenuItem::BackToMainMenu);
			break;

		case Input::Key::Enter:
			switch (selectedOptionsMenuItem)
			{
			case Game::OptionsMenuItem::ColorTheme:
				currentMenu = Menu::ColorThemes;
				break;

			case Game::OptionsMenuItem::MusicAndSounds:
				currentMenu = Menu::MusicAndSounds;
				break;

			case Game::OptionsMenuItem::Credits:
				currentMenu = Menu::Credits;
				break;

			case Game::OptionsMenuItem::BackToMainMenu:
				selectedOptionsMenuItem = OptionsMenuItem::ColorTheme;
				currentMenu = Menu::Main;
				break;

			default:
				throw Exception(L"Variable 'selectedOptionsMenuItem' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
			}
			break;

		case Input::Key::Escape:
			selectedOptionsMenuItem = OptionsMenuItem::ColorTheme;
			currentMenu = Menu::Main;
			break;
		}
	}
}

Game::~Game()
{
	Console::ClearScreen();
}

void Game::RenderLogo(const std::wstring& logoContent)
{
	size_t companyLogoFileContentLength = logoContent.length();
	for (size_t i = 0; i < companyLogoFileContentLength; i++)
	{
		std::wcout << logoContent[i];

		if (logoContent[i] == '\n')
		{
			Console::WaitForMilliseconds(50);
		}
	}

	Console::WaitForMilliseconds(2000);
	Console::ClearScreen();
}

void Game::RenderMenu()
{
	switch (currentMenu)
	{
	case Game::Menu::Main:
		std::wcout << mainMenuFileContent;
		break;
	case Game::Menu::Options:
		std::wcout << optionsMenuFileContent;
		break;
	case Game::Menu::Tutorial:
		std::wcout << tutorialPagesFileContent[currentPage];
		break;
	case Game::Menu::ColorThemes:
		std::wcout << colorThemesMenuFileContent;
		break;
	case Game::Menu::MusicAndSounds:
		std::wcout << musicAndSoundsMenuFileContent;
		break;
	case Game::Menu::Credits:
		std::wcout << creditsMenuFileContent;
		break;
	case Game::Menu::Difficulties:
		std::wcout << difficultiesMenuFileContent;
		break;
	default:
		throw Exception(L"Variable 'currentMenu' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	Console::ResetCursorPosition();
}

Game& Game::GetInstance()
{
	static Game game;
	return game;
}

void Game::Initialize()
{
	// Set console properties:
	Console::SetUnicodeCodepage();
	Console::SetDimensions(windowWidth, windowHeight);
	Console::HideCursor();
	Console::DisableMaximizeButton();
	Console::DisableScrollBars();
	Console::SetTitle(title);
	Console::SetFont(gameFontName, gameFontSize);
	Console::SetWindowPositionOnScreenCenter();

	// Read logos:
	companyLogoFileContent = FileManager::ReadTextFile(companyLogoFileName);
	gameLogoFileContent = FileManager::ReadTextFile(gameLogoFileName);

	// Read menus:
	mainMenuFileContent = FileManager::ReadTextFile(mainMenuFileName);
	optionsMenuFileContent = FileManager::ReadTextFile(optionsMenuFileName);
	colorThemesMenuFileContent = FileManager::ReadTextFile(colorThemesMenuFileName);
	musicAndSoundsMenuFileContent = FileManager::ReadTextFile(musicAndSoundsMenuFileName);
	difficultiesMenuFileContent = FileManager::ReadTextFile(difficultiesMenuFileName);

	// Read tutorial:
	for (int i = 0; i < TUTORIAL_PAGES_COUNT; i++)
	{
		tutorialPagesFileContent[i] = FileManager::ReadTextFile(tutorialPagesFileNames[i]);
	}

	// Read credits:
	creditsMenuFileContent = FileManager::ReadTextFile(creditsMenuFileName);

	// Set color theme:
	ReadColorThemeFromFile();
	SetColorTheme();
	SetPlusSignOnColorThemeMenuItem();

	isRunning = true;
}

bool Game::IsRunning() const
{
	return isRunning;
}

void Game::HandleInputDifficultiesMenu()
{
	if (Input::PressKey())
	{
		Input::Key pressedKey = Input::GetPressedKey();

		switch (pressedKey)
		{
		case Input::Key::ArrowUp:
			MoveMenuItemUp(selectedDifficultiesMenuItem, DifficultiesMenuItem::Easy, DifficultiesMenuItem::BackToMainMenu);
			break;

		case Input::Key::ArrowDown:
			MoveMenuItemDown(selectedDifficultiesMenuItem, DifficultiesMenuItem::Easy, DifficultiesMenuItem::BackToMainMenu);
			break;

		case Input::Key::Enter:
			switch (selectedDifficultiesMenuItem)
			{
			case Game::DifficultiesMenuItem::Easy:
				difficulty = Difficulty::Easy;
				// TODO: Start the game
				break;

			case Game::DifficultiesMenuItem::Normal:
				difficulty = Difficulty::Normal;
				// TODO: Start the game
				break;

			case Game::DifficultiesMenuItem::Hard:
				difficulty = Difficulty::Hard;
				// TODO: Start the game
				break;

			case Game::DifficultiesMenuItem::BackToMainMenu:
				difficulty = Difficulty::None;
				selectedDifficultiesMenuItem = Game::DifficultiesMenuItem::Easy;
				currentMenu = Menu::Main;
				break;

			default:
				throw Exception(L"Variable 'selectedDifficultiesMenuItem' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
			}
			break;

		case Input::Key::Escape:
			difficulty = Difficulty::None;
			selectedDifficultiesMenuItem = DifficultiesMenuItem::Easy;
			currentMenu = Menu::Main;
			break;
		}
	}
}

void Game::HandleInput()
{
	switch (currentScene)
	{
	case Game::Scene::StartScreen:
		// No code
		break;

	case Game::Scene::Menu:
		HandleInputMenu();
		break;

	case Game::Scene::Game:
		// TODO: Write code
		break;

	default:
		throw Exception(L"Variable 'currentScene' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}
}

void Game::Update()
{
	switch (currentScene)
	{
	case Scene::StartScreen:
		// No code
		break;

	case Scene::Menu:
		UpdateMenu();
		break;

	case Scene::Game:
		break;

	default:
		throw Exception(L"Variable 'currentScene' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}
}

void Game::Render()
{
	switch (currentScene)
	{
	case Game::Scene::StartScreen:
		RenderLogo(companyLogoFileContent);
		RenderLogo(gameLogoFileContent);

		// After rendering logos we don't need them anymore:
		companyLogoFileContent.clear();
		gameLogoFileContent.clear();

		currentScene = Scene::Menu;
		break;

	case Game::Scene::Menu:
		RenderMenu();
		break;

	case Game::Scene::Game:
		// TODO: Write code
		break;

	default:
		throw Exception(L"Variable 'currentScene' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}
}

void Game::UpdateOptionsMenu()
{
	// --- REMOVING ARROW FROM PREVIOUS SELECTED ITEM ---
	size_t arrowPosition = optionsMenuFileContent.find(L"->");
	if (arrowPosition != std::wstring::npos)
	{
		optionsMenuFileContent[arrowPosition] = ' ';
		optionsMenuFileContent[arrowPosition + 1] = ' ';
	}

	// --- SET ARROW ON NEW SELECTED ITEM ---
	// In the menu we need to only set arrow between '[" and ']' brackyes.
	// So algorithm will be next:

	// 1. Find selected menu item first character position in file content:
	size_t foundPosition;
	switch (selectedOptionsMenuItem)
	{
	case Game::OptionsMenuItem::ColorTheme:
		foundPosition = optionsMenuFileContent.find(L"Color theme");
		break;

	case Game::OptionsMenuItem::MusicAndSounds:
		foundPosition = optionsMenuFileContent.find(L"Music & Sounds");
		break;

	case Game::OptionsMenuItem::Credits:
		foundPosition = optionsMenuFileContent.find(L"Credits");
		break;

	case Game::OptionsMenuItem::BackToMainMenu:
		foundPosition = optionsMenuFileContent.find(L"Back to main menu");
		break;

	default:
		throw Exception(L"Variable 'selectedOptionsMenuItem' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	if (foundPosition == std::wstring::npos)
	{
		throw Exception(L"Variable 'foundPosition' == std::wstring::npos", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	// 2. Descrease its value by 4, because open '[' is on 4 characters left:
	foundPosition -= 4;

	// 3. Replace two whitespaces (' ') on characters '-' and '>':
	optionsMenuFileContent[foundPosition] = '-';
	optionsMenuFileContent[foundPosition + 1] = '>';
}

void Game::UpdateDifficultiesMenu()
{
	// --- REMOVING ARROW FROM PREVIOUS SELECTED ITEM ---
	size_t arrowPosition = difficultiesMenuFileContent.find(L"->");
	if (arrowPosition != std::wstring::npos)
	{
		difficultiesMenuFileContent[arrowPosition] = ' ';
		difficultiesMenuFileContent[arrowPosition + 1] = ' ';
	}

	// --- SET ARROW ON NEW SELECTED ITEM ---
	// In the menu we need to only set arrow between '[" and ']' brackyes.
	// So algorithm will be next:

	// 1. Find selected menu item first character position in file content:
	size_t foundPosition;
	switch (selectedDifficultiesMenuItem)
	{
	case DifficultiesMenuItem::Easy:
		foundPosition = difficultiesMenuFileContent.find(L"Easy");
		break;

	case DifficultiesMenuItem::Normal:
		foundPosition = difficultiesMenuFileContent.find(L"Normal");
		break;

	case DifficultiesMenuItem::Hard:
		foundPosition = difficultiesMenuFileContent.find(L"Hard");
		break;

	case DifficultiesMenuItem::BackToMainMenu:
		foundPosition = difficultiesMenuFileContent.find(L"Back to main menu");
		break;

	default:
		throw Exception(L"Variable 'selectedDifficultiesMenuItem' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	if (foundPosition == std::wstring::npos)
	{
		throw Exception(L"Variable 'foundPosition' == std::wstring::npos", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	// 2. Descrease its value by 4, because open '[' is on 4 characters left:
	foundPosition -= 4;

	// 3. Replace two whitespaces (' ') on characters '-' and '>':
	difficultiesMenuFileContent[foundPosition] = '-';
	difficultiesMenuFileContent[foundPosition + 1] = '>';
}

void Game::UpdateColorThemesMenu()
{
	// --- REMOVING ARROW FROM PREVIOUS SELECTED ITEM ---
	size_t arrowPosition = colorThemesMenuFileContent.find(L"->");
	if (arrowPosition != std::wstring::npos)
	{
		colorThemesMenuFileContent[arrowPosition] = ' ';
		colorThemesMenuFileContent[arrowPosition + 1] = ' ';
	}

	// --- SET ARROW ON NEW SELECTED ITEM ---
	// In the menu we need to only set arrow between '[" and ']' brackyes.
	// So algorithm will be next:

	// 1. Find selected menu item first character position in file content:
	size_t foundPosition;
	switch (selectedColorThemesMenuItem)
	{
	case ColorThemesMenuItem::WhiteBlack:
		foundPosition = colorThemesMenuFileContent.find(L"White   Black");
		break;

	case ColorThemesMenuItem::BlueAqua:
		foundPosition = colorThemesMenuFileContent.find(L"Blue    Aqua");
		break;

	case ColorThemesMenuItem::BlackWhite:
		foundPosition = colorThemesMenuFileContent.find(L"Black   White");
		break;

	case ColorThemesMenuItem::PurpleYellow:
		foundPosition = colorThemesMenuFileContent.find(L"Purple  Yellow");
		break;

	default:
		throw Exception(L"Variable 'selectedColorThemesMenuItem' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	if (foundPosition == std::wstring::npos)
	{
		throw Exception(L"Variable 'foundPosition' == std::wstring::npos", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	// 2. Descrease its value by 8, because open '[' is on 8 characters left:
	foundPosition -= 8;

	// 3. Replace two whitespaces (' ') on characters '-' and '>':
	colorThemesMenuFileContent[foundPosition] = '-';
	colorThemesMenuFileContent[foundPosition + 1] = '>';
}

void Game::ReadColorThemeFromFile()
{
	std::wifstream fileStream(colorThemeInfoFileName);

	if (!fileStream.is_open())
	{
		WriteColorThemeToFile();
		return;
	}

	int colorThemeInteger;
	fileStream >> colorThemeInteger;
	currentColorTheme = static_cast<ColorTheme>(colorThemeInteger);

	fileStream.close();
}

void Game::WriteColorThemeToFile() const
{
	std::wofstream fileStream(colorThemeInfoFileName);
	fileStream << static_cast<int>(currentColorTheme);
	fileStream.close();
}

void Game::SetColorTheme() const
{
	switch (currentColorTheme)
	{
	case Game::ColorTheme::WhiteBlack:
		Console::SetFontColor(Console::Color::White);
		Console::SetBackgroundColor(Console::Color::Black);
		break;

	case Game::ColorTheme::BlueAqua:
		Console::SetFontColor(Console::Color::Blue);
		Console::SetBackgroundColor(Console::Color::Aqua);
		break;

	case Game::ColorTheme::BlackWhite:
		Console::SetFontColor(Console::Color::Black);
		Console::SetBackgroundColor(Console::Color::White);
		break;

	case Game::ColorTheme::PurpleYellow:
		Console::SetFontColor(Console::Color::Purple);
		Console::SetBackgroundColor(Console::Color::LightYellow);
		break;

	default:
		throw Exception(L"Variable 'currentColorTheme' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}
}

void Game::SetPlusSignOnColorThemeMenuItem()
{
	// --- REMOVE '+' SIGN ON PREVIOUS POSITION ---
	size_t foundPosition = colorThemesMenuFileContent.find(L"{+}");
	if (foundPosition != std::wstring::npos)
	{
		colorThemesMenuFileContent[foundPosition + 1] = ' ';
	}

	// --- SET '+' SIGN ON NEW POSITION ---
	switch (currentColorTheme)
	{
	case ColorTheme::WhiteBlack:
		foundPosition = colorThemesMenuFileContent.find(L"White   Black");
		break;

	case ColorTheme::BlueAqua:
		foundPosition = colorThemesMenuFileContent.find(L"Blue    Aqua");
		break;

	case ColorTheme::BlackWhite:
		foundPosition = colorThemesMenuFileContent.find(L"Black   White");
		break;

	case ColorTheme::PurpleYellow:
		foundPosition = colorThemesMenuFileContent.find(L"Purple  Yellow");
		break;

	default:
		throw Exception(L"Variable 'currentColorTheme' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	if (foundPosition == std::wstring::npos)
	{
		throw Exception(L"Variable 'foundPosition' == std::wstring::npos", __FILEW__, __FUNCTIONW__, __LINE__);
	}

	foundPosition -= 3;
	colorThemesMenuFileContent[foundPosition] = '+';
}

void Game::HandleInputColorThemesMenu()
{
	if (Input::PressKey())
	{
		Input::Key pressedKey = Input::GetPressedKey();

		switch (pressedKey)
		{
		case Input::Key::ArrowUp:
			MoveMenuItemUp(selectedColorThemesMenuItem, ColorThemesMenuItem::WhiteBlack, ColorThemesMenuItem::BackToMainMenu);
			break;

		case Input::Key::ArrowDown:
			MoveMenuItemDown(selectedColorThemesMenuItem, ColorThemesMenuItem::WhiteBlack, ColorThemesMenuItem::BackToMainMenu);
			break;

		case Input::Key::Enter:
			switch (selectedColorThemesMenuItem)
			{
			case Game::ColorThemesMenuItem::WhiteBlack:
				currentColorTheme = ColorTheme::WhiteBlack;
				SetColorTheme();
				WriteColorThemeToFile();
				SetPlusSignOnColorThemeMenuItem();
				break;

			case Game::ColorThemesMenuItem::BlueAqua:
				currentColorTheme = ColorTheme::BlueAqua;
				SetColorTheme();
				WriteColorThemeToFile();
				SetPlusSignOnColorThemeMenuItem();
				break;

			case Game::ColorThemesMenuItem::BlackWhite:
				currentColorTheme = ColorTheme::BlackWhite;
				SetColorTheme();
				WriteColorThemeToFile();
				SetPlusSignOnColorThemeMenuItem();
				break;

			case Game::ColorThemesMenuItem::PurpleYellow:
				currentColorTheme = ColorTheme::PurpleYellow;
				SetColorTheme();
				WriteColorThemeToFile();
				SetPlusSignOnColorThemeMenuItem();
				break;

			case Game::ColorThemesMenuItem::BackToMainMenu:
				selectedColorThemesMenuItem = ColorThemesMenuItem::WhiteBlack;
				currentMenu = Menu::Options;
				break;

			default:
				throw Exception(L"Variable 'selectedColorThemesMenuItem' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
			}
			break;

		case Input::Key::Escape:
			selectedColorThemesMenuItem = ColorThemesMenuItem::WhiteBlack;
			currentMenu = Menu::Options;
			break;
		}
	}
}

void Game::HandleException(const Exception& exc)
{
	Console::ClearScreen();

	std::wcout << L"ERROR!\n";
	std::wcout << L"Message:  " << exc.Message() << std::endl;
	std::wcout << L"File:     " << exc.FileName() << std::endl;
	std::wcout << L"Function: " << exc.FunctionName() << std::endl;
	std::wcout << L"Line:     " << exc.LineNumber() << std::endl;

	Console::WaitForPressKey();
}