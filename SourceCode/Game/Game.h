#pragma once
#include <string>

class Game
{
private:
	Game() = default;
	~Game();

	bool isRunning = false;

	// Console properties:
	const std::wstring title = L"Console Sea Battle";
	const std::wstring gameFontName = L"Consolas";
	const int gameFontSize = 30;
	const int windowWidth = 71;
	const int windowHeight = 23;

	std::wstring companyLogoFileContent;
	const std::wstring companyLogoFileName = L"Resources/StartScreen/CompanyLogo.txt";

	std::wstring gameLogoFileContent;
	const std::wstring gameLogoFileName = L"Resources/StartScreen/GameLogo.txt";

	std::wstring mainMenuFileContent;
	const std::wstring mainMenuFileName = L"Resources/Menus/MainMenu.txt";

	std::wstring optionsMenuFileContent;
	const std::wstring optionsMenuFileName = L"Resources/Menus/OptionsMenu.txt";

	std::wstring colorThemesMenuFileContent;
	const std::wstring colorThemesMenuFileName = L"Resources/Menus/ColorThemesMenu.txt";

	std::wstring musicAndSoundsMenuFileContent;
	const std::wstring musicAndSoundsMenuFileName = L"Resources/Menus/MusicAndSoundsMenu.txt";

	std::wstring creditsMenuFileContent;
	const std::wstring creditsMenuFileName = L"Resources/Credits/Credits.txt";

	std::wstring difficultiesMenuFileContent;
	const std::wstring difficultiesMenuFileName = L"Resources/Menus/DifficultiesMenu.txt";

	static const int TUTORIAL_PAGES_COUNT = 3;
	std::wstring tutorialPagesFileContent[TUTORIAL_PAGES_COUNT];
	const std::wstring tutorialPagesFileNames[TUTORIAL_PAGES_COUNT] =
	{
		L"Resources/Tutorial/TutorialPage1.txt",
		L"Resources/Tutorial/TutorialPage2.txt",
		L"Resources/Tutorial/TutorialPage3.txt"
	};
	int currentPage = 0;

	const std::wstring colorThemeInfoFileName = L"Resources/Data/ColorTheme.bin";

	enum class Scene
	{
		StartScreen,
		Menu,
		Game
	} currentScene = Scene::StartScreen;

	enum class Menu
	{
		Main,
		Options,
		Tutorial,
		ColorThemes,
		MusicAndSounds,
		Credits,
		Difficulties
	} currentMenu = Menu::Main;

	enum class MainMenuItem
	{
		StartGame,
		Options,
		Tutorial,
		Exit
	} selectedMainMenuItem = MainMenuItem::StartGame;

	enum class OptionsMenuItem
	{
		ColorTheme,
		MusicAndSounds,
		Credits,
		BackToMainMenu
	} selectedOptionsMenuItem = OptionsMenuItem::ColorTheme;

	enum class DifficultiesMenuItem
	{
		Easy,
		Normal,
		Hard,
		BackToMainMenu
	} selectedDifficultiesMenuItem = DifficultiesMenuItem::Easy;

	enum class ColorThemesMenuItem
	{
		WhiteBlack,
		BlueAqua,
		BlackWhite,
		PurpleYellow,
		BackToMainMenu
	} selectedColorThemesMenuItem = ColorThemesMenuItem::WhiteBlack;

	enum class ColorTheme
	{
		WhiteBlack,
		BlueAqua,
		BlackWhite,
		PurpleYellow,
	} currentColorTheme = ColorTheme::WhiteBlack; // default value

	enum class Difficulty
	{
		Easy,
		Normal,
		Hard,
		None
	} difficulty = Difficulty::None;

	void ReadColorThemeFromFile();
	void WriteColorThemeToFile() const;
	void SetColorTheme() const;
	void SetPlusSignOnColorThemeMenuItem();

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

	void HandleInputMenu();
	void HandleInputMainMenu();
	void HandleInputTutorialMenu();
	void HandleInputCreditsMenu();
	void HandleInputOptionsMenu();
	void HandleInputDifficultiesMenu();
	void HandleInputColorThemesMenu();

	void UpdateMenu();
	void UpdateMainMenu();
	void UpdateOptionsMenu();
	void UpdateDifficultiesMenu();
	void UpdateColorThemesMenu();

	void RenderLogo(const std::wstring& logoContent);
	void RenderMenu();

public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	static Game& GetInstance();

	void Initialize();
	bool IsRunning() const;
	void HandleInput();
	void Update();
	void Render();

#pragma region Exception
	class Exception
	{
	private:
		std::wstring message;
		std::wstring functionName;
		std::wstring fileName;
		unsigned int lineNumber;

	public:
		Exception(
			const std::wstring& message = L"No message", 
			const std::wstring& functionName = L"No function name", 
			const std::wstring fileName = L"No file name",
			unsigned int lineNumber = 0)
			: message(message), functionName(functionName), fileName(fileName), lineNumber(lineNumber)
		{ }

		const std::wstring& Message() const { return message; }
		const std::wstring& FunctionName() const { return functionName; }
		const std::wstring& FileName() const { return fileName; }
		unsigned int LineNumber() const { return lineNumber; }
	};

	static void HandleException(const Exception& exc);
#pragma endregion
};