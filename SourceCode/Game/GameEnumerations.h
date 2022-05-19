#pragma once

enum class Scene
{
	StartScreen,
	Menu,
	Game
};

enum class ColorTheme
{
	WhiteBlack,
	BlueAqua,
	BlackWhite,
	PurpleYellow,
};

enum class Difficulty
{
	Easy,
	Normal,
	Hard,
	None
};

enum class Logo
{
	Company,
	Game
};

#pragma region MenuEnumerations
enum class Menu
{
	Main,
	Options,
	Tutorial,
	ColorThemes,
	Audio,
	Credits,
	Difficulties
};

enum class MainMenuItem
{
	StartGame,
	Options,
	Tutorial,
	Exit
};

enum class OptionsMenuItem
{
	ColorTheme,
	Audio,
	Credits,
	BackToMainMenu
};

enum class DifficultiesMenuItem
{
	Easy,
	Normal,
	Hard,
	BackToMainMenu
};

enum class ColorThemesMenuItem
{
	WhiteBlack,
	BlueAqua,
	BlackWhite,
	PurpleYellow,
	BackToOptionsMenu
};

enum class AudioMenuItem
{
	MusicOn,
	MusicOff,
	SoundsOn,
	SoundsOff,
	BackToOptionsMenu
};
#pragma endregion
