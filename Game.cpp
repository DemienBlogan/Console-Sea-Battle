#include "Game.h"

Game& Game::GetInstance()
{
	static Game game;
	return game;
}

void Game::Initialize()
{
	// TODO: Write code
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
	// TODO: Write code
}

void Game::HandleException(const Exception& exc)
{
	// TODO: Write code
}