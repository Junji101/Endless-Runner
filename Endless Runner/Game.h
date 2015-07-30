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
	int mCharX;			/* Character pos x */
	int mCharY;			/* Character pos y */
	//Inputting Velocities for Gravity
	int mVelX;			/* Character velocity x */
	int mVelY;			/* Character velocity y */
	int mGrav;			/* Velocity downward fo gravity */
	int mJump;			/* Jump Velocity */
	int mBoxCount;		/* Counts objects on screen */
	//Rect for later use
	SDL_Rect mTempRect[10];

	bool mChanged;		/* Check if screen changed */
	bool mBox;			/* Check if box is made */
	bool mDone;			/* Check if done */
	//Private Methods
	void SetPhysics();
	int AddRect();
	int Move();
	int Input();
	int Update();
	int Draw();
	//Drawing Functions
	int DrawBackG();
	int DrawChar();
	int DrawFloor();
	int DrawStuff(int RectNum);

	SDL_Window* mWindow;		/* Window from SDL */
	SDL_Renderer* mRenderer;	/* The window renderer */
	SDL_Texture* mTexture;		/* Current displayed texture */
	SDL_Texture* mChar;			/* Texture for Hero */
	SDL_Texture* mGround;		/* Texture for ground */
	SDL_Rect* mRects[10];
	SDL_Rect* LoadRect(int a[2], int b[2],int c,int d);		/* Rand Rectangle Function */
	SDL_Texture* LoadTexture( std::string path );	/* Load Texture from file */
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
