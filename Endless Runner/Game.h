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
	int mBoxCount;		/* Counts objects on screen */
	//Rect for later use
	SDL_Rect mTempRect[10];
	SDL_Rect mTempBack[4];

	bool mChanged;		/* Check if screen changed */
	bool mDone;			/* Check if done */
	//Private Methods
	void SetPhysics();
	int SetSound();
	//
	void SetBackG();
	int GetRectNum();	/* Gets the num of an empty Rect */
	int AddRect();		/* Adds a rect to a memory alloc in mRects[] */
	int AddBackG();
	int CharFrameNum(int vel, int time);	/*Gets num of Frame to use from char */
	int BackFrameNum(int time);
	int Move();
	int Input();
	int Update();
	int Draw();
	//Drawing Functions
	int DrawStartUp();
	int DrawBackG();
	int DrawChar();
	int DrawFloor();
	int DrawStuff();
	int DrawEnd();
	//Handlers
	void RectHandler();	/* Handles the Rectangles on screen */
	int BackGHandler();

	SDL_Window* mWindow;		/* Window from SDL */
	SDL_Renderer* mRenderer;	/* The window renderer */
	SDL_Texture* mTexture;		/* Current displayed texture */
	SDL_Texture* mStartText;	/* Texture for Stat Up Screen */
	SDL_Texture* mChar;			/* Texture for Hero */
	SDL_Texture* mGround;		/* Texture for ground */
	SDL_Texture* mBye;			/* Texture for End Screen */
	SDL_Rect* mRects[10];
	SDL_Rect* mBackG[4];
	SDL_Rect* GetFrameRect(int frame, int frameWidth, int frameHeight);
	SDL_Rect* LoadRect(int a[2], int b[2],int c,int d);		/* Rand Rectangle Function */
	SDL_Texture* LoadTexture( std::string path );	/* Load Texture from file */
	//Music & Sound
	
	Mix_Music* mMusic;
	Mix_Chunk* mBoom;
	Mix_Chunk* mPound;

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
