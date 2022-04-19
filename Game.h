#pragma once

#include <string>

class Game
{
private:
	Game() = default;

	bool isRunning = false;

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
		std::string message;
		std::string functionName;
		std::string fileName;
		unsigned int lineNumber;

	public:
		Exception(const std::string& message, const std::string& functionName, const std::string fileName, unsigned int lineNumber)
			: message(message), functionName(functionName), fileName(fileName), lineNumber(lineNumber)
		{ }

		const std::string& Message() const { return message; }
		const std::string& FunctionName() const { return functionName; }
		const std::string& FileName() const { return fileName; }
		unsigned int LineNumber() const { return lineNumber; }
	};

	static void HandleException(const Exception& exc);
#pragma endregion
};