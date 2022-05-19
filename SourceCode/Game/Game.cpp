#include "Game.h"
#include <iostream>
#include "../Console/Console.h"
#include "../FileManager/FileManager.h"
#include "../Input/Input.h"
#include "../Debug/Debug.h"

Game::~Game()
{
	Console::ClearScreen();
}

void Game::ReadColorThemeFromFile()
{
	int colorThemeInteger;
	bool success = fileManager.ReadIntFromFile(colorThemeInfoFileName, colorThemeInteger);
	CHECK_EXPRESSION(success);
	currentColorTheme = ColorTheme(colorThemeInteger);
}

void Game::SetColorTheme() const
{
	CHECK_BOUNDS(currentColorTheme, ColorTheme::WhiteBlack, ColorTheme::PurpleYellow);

	switch (currentColorTheme)
	{
	case ColorTheme::WhiteBlack:
		Console::SetFontColor(Console::Color::White);
		Console::SetBackgroundColor(Console::Color::Black);
		break;

	case ColorTheme::BlueAqua:
		Console::SetFontColor(Console::Color::Blue);
		Console::SetBackgroundColor(Console::Color::Aqua);
		break;

	case ColorTheme::BlackWhite:
		Console::SetFontColor(Console::Color::Black);
		Console::SetBackgroundColor(Console::Color::White);
		break;

	case ColorTheme::PurpleYellow:
		Console::SetFontColor(Console::Color::Purple);
		Console::SetBackgroundColor(Console::Color::LightYellow);
		break;
	}
}

void Game::SetPlusSignOnColorThemeMenuItem()
{
	std::wstring& content = fileManager.GetMenuContent(Menu::ColorThemes);

	// --- REMOVE '+' SIGN ON PREVIOUS POSITION ---
	size_t foundPosition = content.find(L"{+}");
	if (foundPosition != std::wstring::npos)
	{
		content[foundPosition + 1] = ' ';
	}

	// --- SET '+' SIGN ON NEW POSITION ---
	CHECK_BOUNDS(currentColorTheme, ColorTheme::WhiteBlack, ColorTheme::PurpleYellow);
	switch (currentColorTheme)
	{
	case ColorTheme::WhiteBlack:
		foundPosition = content.find(L"White   Black");
		break;

	case ColorTheme::BlueAqua:
		foundPosition = content.find(L"Blue    Aqua");
		break;

	case ColorTheme::BlackWhite:
		foundPosition = content.find(L"Black   White");
		break;

	case ColorTheme::PurpleYellow:
		foundPosition = content.find(L"Purple  Yellow");
		break;
	}

	CHECK_EXPRESSION(foundPosition != std::wstring::npos);

	foundPosition -= 3;
	content[foundPosition] = '+';
}

void Game::SetPlusSignOnAudioMenuItem()
{
	std::wstring& content = fileManager.GetMenuContent(Menu::Audio);

	// --- REMOVE '+' SIGN ON PREVIOUS POSITION ---
	// On music first:
	size_t foundPosition = content.find(L"{+}");
	if (foundPosition != std::wstring::npos)
		content[foundPosition + 1] = ' ';
	// On sounds second:
	foundPosition = content.rfind(L"{+}");
	if (foundPosition != std::wstring::npos)
		content[foundPosition + 1] = ' ';

	// --- SET '+' SIGN ON NEW POSITION ---
	// On music first:
	foundPosition = content.find(audioManager.IsMusicOn() ? L"On" : L"Off");
	CHECK_EXPRESSION(foundPosition != std::wstring::npos);
	foundPosition -= 3;
	content[foundPosition] = '+';
	// On sounds second:
	foundPosition = content.rfind(audioManager.IsSoundsOn() ? L"On" : L"Off");
	CHECK_EXPRESSION(foundPosition != std::wstring::npos);
	foundPosition -= 3;
	content[foundPosition] = '+';
}

#pragma region HandleInputMethods
void Game::HandleInputMenu()
{
	CHECK_BOUNDS(currentMenu, Menu::Main, Menu::Difficulties);

	switch (currentMenu)
	{
	case Menu::Main:
		HandleInputMainMenu();
		break;

	case Menu::Options:
		HandleInputOptionsMenu();
		break;

	case Menu::Tutorial:
		HandleInputTutorialMenu();
		break;

	case Menu::ColorThemes:
		HandleInputColorThemesMenu();
		break;

	case Menu::Audio:
		HandleInputAudioMenu();
		break;

	case Menu::Credits:
		HandleInputCreditsMenu();
		break;

	case Menu::Difficulties:
		HandleInputDifficultiesMenu();
		break;
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
			audioManager.PlaySound(Audio::ChangeMenuItemSound);
			break;

		case Input::Key::ArrowDown:
			MoveMenuItemDown(selectedMainMenuItem, MainMenuItem::StartGame, MainMenuItem::Exit);
			audioManager.PlaySound(Audio::ChangeMenuItemSound);
			break;

		case Input::Key::Enter:
			audioManager.PlaySound(Audio::SelectMenuItemSound);

			CHECK_BOUNDS(selectedMainMenuItem, MainMenuItem::StartGame, MainMenuItem::Exit);

			switch (selectedMainMenuItem)
			{
			case MainMenuItem::StartGame:
				currentMenu = Menu::Difficulties;
				break;

			case MainMenuItem::Options:
				currentMenu = Menu::Options;
				break;

			case MainMenuItem::Tutorial:
				currentMenu = Menu::Tutorial;
				break;

			case MainMenuItem::Exit:
				isRunning = false;
				break;
			}
			break;

		case Input::Key::Escape:
			audioManager.PlaySound(Audio::SelectMenuItemSound);
			isRunning = false;
			break;
		}
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
			if (currentTutorialPage > 0)
			{
				audioManager.PlaySound(Audio::ChangeMenuItemSound);
				currentTutorialPage--;
			}
			break;

		case Input::Key::ArrowRight:
			if (currentTutorialPage < TUTORIAL_PAGES_COUNT - 1)
			{
				audioManager.PlaySound(Audio::ChangeMenuItemSound);
				currentTutorialPage++;
			}
			break;

		case Input::Key::Escape:
			audioManager.PlaySound(Audio::SelectMenuItemSound);
			currentTutorialPage = 0;
			currentMenu = Menu::Main;
			break;
		}
	}
}

void Game::HandleInputCreditsMenu()
{
	if (Input::PressKey())
	{
		Input::Key pressedKey = Input::GetPressedKey();

		switch (pressedKey)
		{
		case Input::Key::Escape:
			audioManager.PlaySound(Audio::SelectMenuItemSound);
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
			audioManager.PlaySound(Audio::ChangeMenuItemSound);
			break;

		case Input::Key::ArrowDown:
			MoveMenuItemDown(selectedOptionsMenuItem, OptionsMenuItem::ColorTheme, OptionsMenuItem::BackToMainMenu);
			audioManager.PlaySound(Audio::ChangeMenuItemSound);
			break;

		case Input::Key::Enter:
			audioManager.PlaySound(Audio::SelectMenuItemSound);

			CHECK_BOUNDS(selectedOptionsMenuItem, OptionsMenuItem::ColorTheme, OptionsMenuItem::BackToMainMenu);

			switch (selectedOptionsMenuItem)
			{
			case OptionsMenuItem::ColorTheme:
				currentMenu = Menu::ColorThemes;
				break;

			case OptionsMenuItem::Audio:
				currentMenu = Menu::Audio;
				break;

			case OptionsMenuItem::Credits:
				currentMenu = Menu::Credits;
				break;

			case OptionsMenuItem::BackToMainMenu:
				selectedOptionsMenuItem = OptionsMenuItem::ColorTheme;
				currentMenu = Menu::Main;
				break;
			}
			break;

		case Input::Key::Escape:
			audioManager.PlaySound(Audio::SelectMenuItemSound);
			selectedOptionsMenuItem = OptionsMenuItem::ColorTheme;
			currentMenu = Menu::Main;
			break;
		}
	}
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
			audioManager.PlaySound(Audio::ChangeMenuItemSound);
			break;

		case Input::Key::ArrowDown:
			MoveMenuItemDown(selectedDifficultiesMenuItem, DifficultiesMenuItem::Easy, DifficultiesMenuItem::BackToMainMenu);
			audioManager.PlaySound(Audio::ChangeMenuItemSound);
			break;

		case Input::Key::Enter:
			audioManager.PlaySound(Audio::SelectMenuItemSound);

			CHECK_BOUNDS(selectedDifficultiesMenuItem, DifficultiesMenuItem::Easy, DifficultiesMenuItem::BackToMainMenu);

			switch (selectedDifficultiesMenuItem)
			{
			case DifficultiesMenuItem::Easy:
				selectedDifficultiesMenuItem = DifficultiesMenuItem::Easy;
				difficulty = Difficulty::Easy;
				currentScene = Scene::Game;
				break;

			case DifficultiesMenuItem::Normal:
				selectedDifficultiesMenuItem = DifficultiesMenuItem::Easy;
				difficulty = Difficulty::Normal;
				currentScene = Scene::Game;
				break;

			case DifficultiesMenuItem::Hard:
				selectedDifficultiesMenuItem = DifficultiesMenuItem::Easy;
				difficulty = Difficulty::Hard;
				currentScene = Scene::Game;
				break;

			case DifficultiesMenuItem::BackToMainMenu:
				difficulty = Difficulty::None;
				selectedDifficultiesMenuItem = DifficultiesMenuItem::Easy;
				currentMenu = Menu::Main;
				break;
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

void Game::HandleInputColorThemesMenu()
{
	if (Input::PressKey())
	{
		Input::Key pressedKey = Input::GetPressedKey();

		switch (pressedKey)
		{
		case Input::Key::ArrowUp:
			MoveMenuItemUp(selectedColorThemesMenuItem, ColorThemesMenuItem::WhiteBlack, ColorThemesMenuItem::BackToOptionsMenu);
			audioManager.PlaySound(Audio::ChangeMenuItemSound);
			break;

		case Input::Key::ArrowDown:
			MoveMenuItemDown(selectedColorThemesMenuItem, ColorThemesMenuItem::WhiteBlack, ColorThemesMenuItem::BackToOptionsMenu);
			audioManager.PlaySound(Audio::ChangeMenuItemSound);
			break;

		case Input::Key::Enter:
			audioManager.PlaySound(Audio::SelectMenuItemSound);

			CHECK_BOUNDS(selectedColorThemesMenuItem, ColorThemesMenuItem::WhiteBlack, ColorThemesMenuItem::BackToOptionsMenu);

			switch (selectedColorThemesMenuItem)
			{
			case ColorThemesMenuItem::WhiteBlack:
				currentColorTheme = ColorTheme::WhiteBlack;
				SetColorTheme();
				fileManager.WriteIntToFile(colorThemeInfoFileName, int(currentColorTheme));
				SetPlusSignOnColorThemeMenuItem();
				break;

			case ColorThemesMenuItem::BlueAqua:
				currentColorTheme = ColorTheme::BlueAqua;
				SetColorTheme();
				fileManager.WriteIntToFile(colorThemeInfoFileName, int(currentColorTheme));
				SetPlusSignOnColorThemeMenuItem();
				break;

			case ColorThemesMenuItem::BlackWhite:
				currentColorTheme = ColorTheme::BlackWhite;
				SetColorTheme();
				fileManager.WriteIntToFile(colorThemeInfoFileName, int(currentColorTheme));
				SetPlusSignOnColorThemeMenuItem();
				break;

			case ColorThemesMenuItem::PurpleYellow:
				currentColorTheme = ColorTheme::PurpleYellow;
				SetColorTheme();
				fileManager.WriteIntToFile(colorThemeInfoFileName, int(currentColorTheme));
				SetPlusSignOnColorThemeMenuItem();
				break;

			case ColorThemesMenuItem::BackToOptionsMenu:
				selectedColorThemesMenuItem = ColorThemesMenuItem::WhiteBlack;
				currentMenu = Menu::Options;
				break;
			}
			break;

		case Input::Key::Escape:
			audioManager.PlaySound(Audio::SelectMenuItemSound);
			selectedColorThemesMenuItem = ColorThemesMenuItem::WhiteBlack;
			currentMenu = Menu::Options;
			break;
		}
	}
}

void Game::HandleInputAudioMenu()
{
	if (Input::PressKey())
	{
		Input::Key pressedKey = Input::GetPressedKey();

		switch (pressedKey)
		{
		case Input::Key::ArrowUp:
			MoveMenuItemUp(selectedAudioMenuItem, AudioMenuItem::MusicOn, AudioMenuItem::BackToOptionsMenu);
			audioManager.PlaySound(Audio::ChangeMenuItemSound);
			break;

		case Input::Key::ArrowDown:
			MoveMenuItemDown(selectedAudioMenuItem, AudioMenuItem::MusicOn, AudioMenuItem::BackToOptionsMenu);
			audioManager.PlaySound(Audio::ChangeMenuItemSound);
			break;

		case Input::Key::Enter:
			CHECK_BOUNDS(selectedAudioMenuItem, AudioMenuItem::MusicOn, AudioMenuItem::BackToOptionsMenu);

			switch (selectedAudioMenuItem)
			{
			case AudioMenuItem::MusicOn:
				if (!audioManager.IsMusicOn())
				{
					audioManager.TurnOnMusic();
					SetPlusSignOnAudioMenuItem();
					audioManager.WriteAudioSettingsToFile();
					audioManager.PlayMusic(Audio::BackgroundMenuMusic, true);
				}
				break;

			case AudioMenuItem::MusicOff:
				if (audioManager.IsMusicOn())
				{
					audioManager.TurnOffMusic();
					SetPlusSignOnAudioMenuItem();
					audioManager.WriteAudioSettingsToFile();
					audioManager.StopMusic();
				}
				break;

			case AudioMenuItem::SoundsOn:
				if (!audioManager.IsSoundsOn())
				{
					audioManager.TurnOnSounds();
					SetPlusSignOnAudioMenuItem();
					audioManager.WriteAudioSettingsToFile();
				}
				break;

			case AudioMenuItem::SoundsOff:
				if (audioManager.IsSoundsOn())
				{
					audioManager.TurnOffSounds();
					SetPlusSignOnAudioMenuItem();
					audioManager.WriteAudioSettingsToFile();
				}
				break;

			case AudioMenuItem::BackToOptionsMenu:
				selectedAudioMenuItem = AudioMenuItem::MusicOn;
				currentMenu = Menu::Options;
				break;
			}
			audioManager.PlaySound(Audio::SelectMenuItemSound);
			break;

		case Input::Key::Escape:
			audioManager.PlaySound(Audio::SelectMenuItemSound);
			selectedAudioMenuItem = AudioMenuItem::MusicOn;
			currentMenu = Menu::Options;
			break;
		}
	}
}

void Game::HandleInputGame()
{
	// TODO: Write code
}
#pragma endregion

#pragma region UpdateMethods
void Game::UpdateMenu()
{
	CHECK_BOUNDS(currentMenu, Menu::Main, Menu::Difficulties);

	switch (currentMenu)
	{
	case Menu::Main:
		UpdateMainMenu();
		break;

	case Menu::Options:
		UpdateOptionsMenu();
		break;

	case Menu::ColorThemes:
		UpdateColorThemesMenu();
		break;

	case Menu::Audio:
		UpdateAudioMenu();
		break;

	case Menu::Difficulties:
		UpdateDifficultiesMenu();
		break;
	}
}

void Game::UpdateMainMenu()
{
	std::wstring& content = fileManager.GetMenuContent(Menu::Main);

	// --- REMOVING ARROW FROM PREVIOUS SELECTED ITEM ---
	size_t arrowPosition = content.find(L"->");
	if (arrowPosition != std::wstring::npos)
	{
		content[arrowPosition] = ' ';
		content[arrowPosition + 1] = ' ';
	}

	// --- SET ARROW ON NEW SELECTED ITEM ---
	// In the menu we need to only set arrow between '[" and ']' brackyes.
	// So algorithm will be next:

	// 1. Find selected menu item first character position in file content:
	size_t foundPosition = std::wstring::npos;

	CHECK_BOUNDS(selectedMainMenuItem, MainMenuItem::StartGame, MainMenuItem::Exit);

	switch (selectedMainMenuItem)
	{
	case MainMenuItem::StartGame:
		foundPosition = content.find(L"Start Game");
		break;

	case MainMenuItem::Options:
		foundPosition = content.find(L"Options");
		break;

	case MainMenuItem::Tutorial:
		foundPosition = content.find(L"Tutorial");
		break;

	case MainMenuItem::Exit:
		foundPosition = content.find(L"Exit");
		break;
	}

	CHECK_EXPRESSION(foundPosition != std::wstring::npos);

	// 2. Descrease its value by 4, because open '[' is on 4 characters left:
	foundPosition -= 4;

	// 3. Replace two whitespaces (' ') on characters '-' and '>':
	content[foundPosition] = '-';
	content[foundPosition + 1] = '>';
}

void Game::UpdateOptionsMenu()
{
	std::wstring& content = fileManager.GetMenuContent(Menu::Options);

	// --- REMOVING ARROW FROM PREVIOUS SELECTED ITEM ---
	size_t arrowPosition = content.find(L"->");
	if (arrowPosition != std::wstring::npos)
	{
		content[arrowPosition] = ' ';
		content[arrowPosition + 1] = ' ';
	}

	// --- SET ARROW ON NEW SELECTED ITEM ---
	// In the menu we need to only set arrow between '[" and ']' brackyes.
	// So algorithm will be next:

	// 1. Find selected menu item first character position in file content:
	size_t foundPosition = std::wstring::npos;

	CHECK_BOUNDS(selectedOptionsMenuItem, OptionsMenuItem::ColorTheme, OptionsMenuItem::BackToMainMenu);

	switch (selectedOptionsMenuItem)
	{
	case OptionsMenuItem::ColorTheme:
		foundPosition = content.find(L"Color theme");
		break;

	case OptionsMenuItem::Audio:
		foundPosition = content.find(L"Audio");
		break;

	case OptionsMenuItem::Credits:
		foundPosition = content.find(L"Credits");
		break;

	case OptionsMenuItem::BackToMainMenu:
		foundPosition = content.find(L"Back to main menu");
		break;
	}

	CHECK_EXPRESSION(foundPosition != std::wstring::npos);

	// 2. Descrease its value by 4, because open '[' is on 4 characters left:
	foundPosition -= 4;

	// 3. Replace two whitespaces (' ') on characters '-' and '>':
	content[foundPosition] = '-';
	content[foundPosition + 1] = '>';
}

void Game::UpdateDifficultiesMenu()
{
	std::wstring& content = fileManager.GetMenuContent(Menu::Difficulties);

	// --- REMOVING ARROW FROM PREVIOUS SELECTED ITEM ---
	size_t arrowPosition = content.find(L"->");
	if (arrowPosition != std::wstring::npos)
	{
		content[arrowPosition] = ' ';
		content[arrowPosition + 1] = ' ';
	}

	// --- SET ARROW ON NEW SELECTED ITEM ---
	// In the menu we need to only set arrow between '[" and ']' brackyes.
	// So algorithm will be next:

	// 1. Find selected menu item first character position in file content:
	size_t foundPosition = std::wstring::npos;

	CHECK_BOUNDS(selectedDifficultiesMenuItem, DifficultiesMenuItem::Easy, DifficultiesMenuItem::BackToMainMenu);

	switch (selectedDifficultiesMenuItem)
	{
	case DifficultiesMenuItem::Easy:
		foundPosition = content.find(L"Easy");
		break;

	case DifficultiesMenuItem::Normal:
		foundPosition = content.find(L"Normal");
		break;

	case DifficultiesMenuItem::Hard:
		foundPosition = content.find(L"Hard");
		break;

	case DifficultiesMenuItem::BackToMainMenu:
		foundPosition = content.find(L"Back to main menu");
		break;
	}

	CHECK_EXPRESSION(foundPosition != std::wstring::npos);

	// 2. Descrease its value by 4, because open '[' is on 4 characters left:
	foundPosition -= 4;

	// 3. Replace two whitespaces (' ') on characters '-' and '>':
	content[foundPosition] = '-';
	content[foundPosition + 1] = '>';
}

void Game::UpdateColorThemesMenu()
{
	std::wstring& content = fileManager.GetMenuContent(Menu::ColorThemes);

	// --- REMOVING ARROW FROM PREVIOUS SELECTED ITEM ---
	size_t arrowPosition = content.find(L"->");
	if (arrowPosition != std::wstring::npos)
	{
		content[arrowPosition] = ' ';
		content[arrowPosition + 1] = ' ';
	}

	// --- SET ARROW ON NEW SELECTED ITEM ---
	// In the menu we need to only set arrow between '[" and ']' brackyes.
	// So algorithm will be next:

	// 1. Find selected menu item first character position in file content:
	size_t foundPosition = std::wstring::npos;

	CHECK_BOUNDS(selectedColorThemesMenuItem, ColorThemesMenuItem::WhiteBlack, ColorThemesMenuItem::BackToOptionsMenu);

	switch (selectedColorThemesMenuItem)
	{
	case ColorThemesMenuItem::WhiteBlack:
		foundPosition = content.find(L"White   Black");
		break;

	case ColorThemesMenuItem::BlueAqua:
		foundPosition = content.find(L"Blue    Aqua");
		break;

	case ColorThemesMenuItem::BlackWhite:
		foundPosition = content.find(L"Black   White");
		break;

	case ColorThemesMenuItem::PurpleYellow:
		foundPosition = content.find(L"Purple  Yellow");
		break;

	case ColorThemesMenuItem::BackToOptionsMenu:
		foundPosition = content.find(L"Back to options menu");
		break;
	}

	CHECK_EXPRESSION(foundPosition != std::wstring::npos);

	if (selectedColorThemesMenuItem == ColorThemesMenuItem::BackToOptionsMenu)
	{
		// 2. Descrease its value by 4, because open '[' is on 4 characters left:
		foundPosition -= 4;
	}
	else
	{
		// 2. Descrease its value by 8, because open '[' is on 8 characters left:
		foundPosition -= 8;
	}

	// 3. Replace two whitespaces (' ') on characters '-' and '>':
	content[foundPosition] = '-';
	content[foundPosition + 1] = '>';
}

void Game::UpdateAudioMenu()
{
	std::wstring& content = fileManager.GetMenuContent(Menu::Audio);

	// --- REMOVING ARROW FROM PREVIOUS SELECTED ITEM ---
	size_t arrowPosition = content.find(L"->");
	if (arrowPosition != std::wstring::npos)
	{
		content[arrowPosition] = ' ';
		content[arrowPosition + 1] = ' ';
	}

	// --- SET ARROW ON NEW SELECTED ITEM ---
	// In the menu we need to only set arrow between '[" and ']' brackyes.
	// So algorithm will be next:

	// 1. Find selected menu item first character position in file content:
	size_t foundPosition = std::wstring::npos;

	CHECK_BOUNDS(selectedAudioMenuItem, AudioMenuItem::MusicOn, AudioMenuItem::BackToOptionsMenu);

	switch (selectedAudioMenuItem)
	{
	case AudioMenuItem::MusicOn:
		foundPosition = content.find(L"On");
		break;

	case AudioMenuItem::MusicOff:
		foundPosition = content.find(L"Off");
		break;

	case AudioMenuItem::SoundsOn:
		foundPosition = content.rfind(L"On");
		break;

	case AudioMenuItem::SoundsOff:
		foundPosition = content.rfind(L"Off");
		break;

	case AudioMenuItem::BackToOptionsMenu:
		foundPosition = content.find(L"Back to options menu");
		break;
	}

	CHECK_EXPRESSION(foundPosition != std::wstring::npos);

	if (selectedAudioMenuItem == AudioMenuItem::BackToOptionsMenu)
	{
		// 2. Descrease its value by 4, because open '[' is on 4 characters left:
		foundPosition -= 4;
	}
	else
	{
		// 2. Descrease its value by 8, because open '[' is on 8 characters left:
		foundPosition -= 8;
	}

	// 3. Replace two whitespaces (' ') on characters '-' and '>':
	content[foundPosition] = '-';
	content[foundPosition + 1] = '>';
}

void Game::UpdateGame()
{
	// TODO: Write code
}
#pragma endregion

#pragma region RenderMethods
void Game::RenderLogo(Logo logo)
{
	const std::wstring& content = fileManager.GetLogoContent(logo);
	size_t length = content.length();

	for (size_t i = 0; i < length; i++)
	{
		std::wcout << content[i];

		if (content[i] == '\n')
			Console::WaitForMilliseconds(50);
	}

	Console::WaitForMilliseconds(2000);
	Console::ClearScreen();
}

void Game::RenderMenu()
{
	CHECK_BOUNDS(currentMenu, Menu::Main, Menu::Difficulties);

	if (currentMenu != Menu::Tutorial)
		std::wcout << fileManager.GetMenuContent(currentMenu);
	else
		std::wcout << fileManager.GetTutorialContent(currentTutorialPage);

	Console::ResetCursorPosition();
}

void Game::RenderGame()
{
	// TODO: Write code
}
#pragma endregion

#pragma region PublicMethods
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

	// Read content from files:
	fileManager.Initialize();

	// Set color theme:
	ReadColorThemeFromFile();
	SetColorTheme();
	SetPlusSignOnColorThemeMenuItem();

	// Set audio settins:
	audioManager.Initialize();
	SetPlusSignOnAudioMenuItem();
	if (audioManager.IsMusicOn())
		audioManager.PlayMusic(Audio::BackgroundMenuMusic, true);

	isRunning = true;
}

bool Game::IsRunning() const
{
	return isRunning;
}

void Game::HandleInput()
{
	CHECK_BOUNDS(currentScene, Scene::StartScreen, Scene::Game);

	switch (currentScene)
	{
	case Scene::Menu:
		HandleInputMenu();
		break;

	case Scene::Game:
		HandleInputGame();
		break;
	}
}

void Game::Update()
{
	audioManager.Update();

	CHECK_BOUNDS(currentScene, Scene::StartScreen, Scene::Game);

	switch (currentScene)
	{
	case Scene::Menu:
		UpdateMenu();
		break;

	case Scene::Game:
		UpdateGame();
		break;
	}
}

void Game::Render()
{
	CHECK_BOUNDS(currentScene, Scene::StartScreen, Scene::Game);

	switch (currentScene)
	{
	case Scene::StartScreen:
		RenderLogo(Logo::Company);
		RenderLogo(Logo::Game);
		currentScene = Scene::Menu;
		break;

	case Scene::Menu:
		RenderMenu();
		break;

	case Scene::Game:
		RenderGame();
		break;
	}
}
#pragma endregion