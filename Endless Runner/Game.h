/*What is function?
 *@param -argument -desc
 *
 *@return desc of what it returns
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
	int mTime;
	int mLastTime;
	int mDeltaTime;
	int mBoxCount;		/* Counts objects on screen */
	//Rect for later use
	SDL_Rect mTempRect[10];

	bool mChanged;		/* Check if screen changed */
	bool mBox;			/* Check if box is made */
	bool mDone;			/* Check if done */
	//Private Methods
	void SetPhysics();
	int GetRectNum();	/* Gets the num of an empty Rect */
	int AddRect();		/* Adds a rect to a memory alloc in mRects[] */
	int GetFrameNum(int vel, int time);	/*Gets num of Frame to use from char */
	int Move();
	int Input();
	int Update();
	int Draw();
	//Drawing Functions
	int DrawBackG();
	int DrawChar();
	int DrawFloor();
	int DrawStuff();
	//Rect Handler
	void RectHandler();	/* Handles the Rectangles on screen */

	SDL_Window* mWindow;		/* Window from SDL */
	SDL_Renderer* mRenderer;	/* The window renderer */
	SDL_Texture* mTexture;		/* Current displayed texture */
	SDL_Texture* mChar;			/* Texture for Hero */
	SDL_Texture* mGround;		/* Texture for ground */
	SDL_Rect* mRects[10];
	SDL_Rect* GetFrameRect(int frame);
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
