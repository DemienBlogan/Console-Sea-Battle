#pragma once
#include <string>

class Game
{
private:
	Game() = default;

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

	enum class Scene
	{
		StartScreen,
		Menu,
		Game
	};
	Scene currentScene = Scene::StartScreen;

	void RenderLogo(const std::wstring& logoContent);

public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	static Game& GetInstance();

	void Initialize();
	bool IsRunning() const;
	void HandleInput();
	void Update(float deltaTime);
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