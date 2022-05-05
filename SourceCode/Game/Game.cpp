#include "Game.h"
#include <iostream>
#include "../Console/Console.h"
#include "../FileManager/FileManager.h"

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

Game& Game::GetInstance()
{
	static Game game;
	return game;
}

void Game::Initialize()
{
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

	isRunning = true;
}

bool Game::IsRunning() const
{
	return isRunning;
}

void Game::HandleInput()
{
	// TODO: Write code
}

void Game::Update(float deltaTime)
{
	// TODO: Write code
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