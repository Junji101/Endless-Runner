/*What is function?
 *Argv = Arguments needed?
 *
 *
 */

#ifndef __GAME_H
#define __GAME_H


/*The games driver class
 *
 */
class GameData
{
	int mGameState;		/* The state of the game */
	bool mChanged;		/* Check if screen changed */
	bool mDone;			/* Check if done */
	//Private Methods
	int Input();
	int Update();
	int Draw();
	//Drawing Functions
	int DrawBackG();
	int DrawChar();
	int DrawFloor();
	int DrawStuff();
	SDL_Window* mWindow;		/* Window from SDL */


	SDL_Renderer* mRenderer;	/* The window renderer */
	SDL_Texture* mTexture;		/* Current displayed texture */
	SDL_Texture* LoadTexture( std::string path );
public:
	//Constructors

	//Public Methods
	int Setup();
	int LoadMedia();
	int Run();
	int Shutdown();
};

extern GameData game;

#endif //__Game_H
