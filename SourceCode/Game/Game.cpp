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
		// TODO: Write code
		break;

	case Game::Scene::Game:
		// TODO: Write code
		break;

	default:
		throw Exception(L"Variable 'currentScene' is incorrect", __FILEW__, __FUNCTIONW__, __LINE__);
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