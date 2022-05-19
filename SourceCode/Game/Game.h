#pragma once
#include "../AudioManager/AudioManager.h"
#include "../FileManager/FileManager.h"

class Game
{
private:
	Game() = default;
	~Game();

	bool isRunning = false;

	// Managers:
	AudioManager& audioManager = AudioManager::GetInstance();
	FileManager& fileManager = FileManager::GetInstance();

	// Console required properties:
	const std::wstring title = L"Console Sea Battle";
	const std::wstring gameFontName = L"Consolas";
	const int gameFontSize = 30;
	const int windowWidth = 71;
	const int windowHeight = 23;

	Scene currentScene = Scene::StartScreen;

	// Tutorial pages info:
	static const int TUTORIAL_PAGES_COUNT = 3;
	int currentTutorialPage = 0;

	// Menus & menu items info:
	Menu currentMenu = Menu::Main;
	MainMenuItem selectedMainMenuItem = MainMenuItem::StartGame;
	OptionsMenuItem selectedOptionsMenuItem = OptionsMenuItem::ColorTheme;
	DifficultiesMenuItem selectedDifficultiesMenuItem = DifficultiesMenuItem::Easy;
	ColorThemesMenuItem selectedColorThemesMenuItem = ColorThemesMenuItem::WhiteBlack;
	AudioMenuItem selectedAudioMenuItem = AudioMenuItem::MusicOn;
	
	// Color theme info:
	ColorTheme currentColorTheme = ColorTheme::WhiteBlack; // default value
	const std::wstring colorThemeInfoFileName = L"Resources/Data/ColorTheme.bin";

	Difficulty difficulty = Difficulty::None;

	void ReadColorThemeFromFile();
	void SetColorTheme() const;

	void SetPlusSignOnColorThemeMenuItem();
	void SetPlusSignOnAudioMenuItem();

	template <typename MenuItem>
	void MoveMenuItemUp(MenuItem& selectedItem, MenuItem firstItem, MenuItem lastItem)
	{
		selectedItem = (selectedItem == firstItem) ? lastItem : static_cast<MenuItem>(static_cast<int>(selectedItem) - 1);
	}

	template <typename MenuItem>
	void MoveMenuItemDown(MenuItem& selectedItem, MenuItem firstItem, MenuItem lastItem)
	{
		selectedItem = (selectedItem == lastItem) ? firstItem : static_cast<MenuItem>(static_cast<int>(selectedItem) + 1);
	}

#pragma region HandleInputMethods
	void HandleInputMenu();
	void HandleInputMainMenu();
	void HandleInputTutorialMenu();
	void HandleInputCreditsMenu();
	void HandleInputOptionsMenu();
	void HandleInputDifficultiesMenu();
	void HandleInputColorThemesMenu();
	void HandleInputAudioMenu();
	void HandleInputGame();
#pragma endregion

#pragma region UpdateMethods
	void UpdateMenu();
	void UpdateMainMenu();
	void UpdateOptionsMenu();
	void UpdateDifficultiesMenu();
	void UpdateColorThemesMenu();
	void UpdateAudioMenu();
	void UpdateGame();
#pragma endregion

#pragma region RenderMethods
	void RenderLogo(Logo logo);
	void RenderMenu();
	void RenderGame();
#pragma endregion

public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	static Game& GetInstance();

	void Initialize();
	bool IsRunning() const;
	void HandleInput();
	void Update();
	void Render();
};