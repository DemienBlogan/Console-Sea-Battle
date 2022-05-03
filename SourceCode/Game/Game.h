#pragma once

#include <string>

class Game
{
private:
	Game() = default;

	bool isRunning = false;

	std::wstring companyLogoFileContent;
	std::wstring companyLogoFileName = L"Resources/StartScreen/CompanyLogo.txt";

	std::wstring gameLogoFileContent;
	std::wstring gameLogoFileName = L"Resources/StartScreen/GameLogo.txt";

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