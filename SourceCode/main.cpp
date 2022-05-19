#include "Game/Game.h"

int main()
{
	Game& game = Game::GetInstance();
	game.Initialize();

	while (game.IsRunning())
	{
		game.HandleInput();
		game.Update();
		game.Render();
	}

	return 0;
}