#include <SDL.h>
#include <string>
#include <SDL_mixer.h>
#include "Game.h"

GameData game;
/*
 * 
 *
*/
int main(int argv, char *args[])
{
	if (game.Setup() < 0)
	{
		return -1;
	}
	if (game.LoadMedia() < 0)
	{
		return -1;
	}
	game.Run();
	game.Shutdown();
	return 0;
}