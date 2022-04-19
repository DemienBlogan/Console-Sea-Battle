#include "Game.h"
#include "Time.h"

int main()
{
	Game& game = Game::GetInstance();

	try
	{
		game.Initialize();
		while (game.IsRunning())
		{
			game.HandleInput();
			game.Update(Time::DeltaTime());
			game.Render();
		}
	}
	catch (const Game::Exception& exc)
	{
		Game::HandleException(exc);
	}

	return 0;
}