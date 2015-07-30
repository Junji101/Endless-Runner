#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Game.h"

const int SDL_DELAY = 10;
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
//Char specifics
const int CHAR_HEIGHT = 50;
const int CHAR_WIDTH = 50;
const int CHAR_SPEED = 3;
//Rect Generation
const int BOX_X_MIN = SCREEN_WIDTH/3;
const int BOX_X_MAX = 2*SCREEN_WIDTH/3;
const int BOX_Y_MIN = SCREEN_HEIGHT/3;
const int BOX_Y_MAX = 2*SCREEN_HEIGHT/3;
const int BOX_HEIGHT_MAX = SCREEN_HEIGHT/5;
const int BOX_WIDTH_MAX = SCREEN_HEIGHT/3;
const int BOX_MAX = 10;
	
/**
 *Sets up the loading of SDL
 *Creates window, renderer, and img flags
 */

void GameData::SetPhysics()
{
	mCharX = 50;
	mCharY = SCREEN_HEIGHT - 100;
	mVelX = 0;
	mVelY = 0;
	mGrav = 9;
	mJump = -27;

}

int GameData::Setup()
{
	if (SDL_Init( SDL_INIT_EVERYTHING ) < 0)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		return -1;
	}

	if ((mWindow = SDL_CreateWindow("Hello World",0,100,SCREEN_WIDTH,SCREEN_HEIGHT,0)) == NULL)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		return -1;
	}


	 //Create renderer for mWindow 
	mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED ); 
	if( mRenderer == NULL ) 
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() ); 
		return -1; 
	}
	else
	{
		//Initialize renderer color 
		SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); 
		//Initialize PNG loading 
		int imgFlags = IMG_INIT_PNG; 
		if( !( IMG_Init( imgFlags ) & imgFlags ) ) 
		{
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ); 
			return -1;
		}
	}
	
	SetPhysics();
	mBox = false;
	mChanged = true;
	return 0;
}

/**
 *Closes all libraries and frees memory allocations
 */
int GameData::Shutdown()
{
	 //Free loaded image 
	SDL_DestroyTexture( mTexture ); 
	//Destroy mWindow 
	SDL_DestroyRenderer( mRenderer ); 
	//Quit SDL subsystems 
	SDL_DestroyWindow( mWindow );
	IMG_Quit();
	SDL_Quit();
	return 0;
}

/**
 * Create Random Rect given limits
 * Rect created with (x,y) ; (h,w)
 * a[1] is max, a[2] is min
 */
SDL_Rect* GameData::LoadRect(int a[2], int b[2], int c, int d)
{
	SDL_Rect* newRect = NULL;

	mTempRect[mBoxCount].x = rand() % (a[0]-a[1]) + a[1];
	mTempRect[mBoxCount].y = rand() % (b[0]-b[1]) + b[1];
	mTempRect[mBoxCount].h = rand() % c;
	mTempRect[mBoxCount].w = rand() % d;
	
	newRect = &mTempRect[mBoxCount];
	return newRect;
}


/**
 * Gets string for path of image
 * Converts from Surface to Texture
 * Returns to texture
 */
SDL_Texture* GameData::LoadTexture( std::string path ) 
{
	//The final texture 
	SDL_Texture* newTexture = NULL; 
	//Load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); 
	if( loadedSurface == NULL ) 
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() ); 
	}
	else
	{
		//Create texture from surface pixels 
		newTexture = SDL_CreateTextureFromSurface( mRenderer, loadedSurface );
		if( newTexture == NULL ) 
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		} 
		//Get rid of old loaded surface 
		SDL_FreeSurface( loadedSurface ); 
	}
	return newTexture;
}

/**
 * Draws floor using mGround texture
 * 
 */
int GameData::DrawFloor()
{
	SDL_Rect fillRect = { 0 , (SCREEN_HEIGHT-50), SCREEN_WIDTH, 50};
	//SDL_SetRenderDrawColor( mRenderer, 0xFF, 0x00, 0x00, 0xFF ); 
	//SDL_RenderFillRect( mRenderer, &fillRect );
	SDL_RenderCopy( mRenderer, mGround, NULL, &fillRect);
	return 0;
}

/**
 * Draw your character on screen
 * Using mChar texture
 */

int GameData::DrawChar()
{
	SDL_Rect fillRect = {mCharX,mCharY, 50, 50};
	SDL_RenderCopy( mRenderer, mChar, NULL, &fillRect);
	return 0;
}

int GameData::AddRect()
{
	SDL_Rect* tempRect = NULL;
	if (mBoxCount != BOX_MAX)
	{
		int xBox[] = {BOX_X_MAX,BOX_X_MIN};
		int yBox[] = {BOX_Y_MAX,BOX_X_MIN};
		tempRect = LoadRect(xBox,yBox,BOX_HEIGHT_MAX, BOX_WIDTH_MAX);
		mRects[mBoxCount] = tempRect;
	}
	return 0;
}

/**
 * Draw a platform
 * Future: Draw Objects
 */
int GameData::DrawStuff(int RectNum)
{
	//SDL_Rect fillRect = { SCREEN_WIDTH/2 , (SCREEN_HEIGHT-200), 500, 50};
	
	SDL_RenderCopy( mRenderer, mGround, NULL, mRects[RectNum]);
	//std::cout << "RectNum = " << mRects[RectNum] << std::endl;
	return 0;
}

/**
*Drawing Background
*/
int GameData::DrawBackG()
{
	SDL_RenderCopy( mRenderer, mTexture, NULL, NULL );
	return 0;
}

/**
 *Drawing to screen function using SDL Rendering
 *
 */
int GameData::Draw()
{
	//SDL_BlitSurface(mHello, NULL, mScreenSurface, NULL);
	//SDL_UpdatemWindowSurface(mWindow);
	//Clear screen 
	SDL_RenderClear( mRenderer ); 
	//Render texture to screen
	DrawBackG();
	DrawFloor();
	DrawChar();
	for(int i = 0;i < mBoxCount; i++)
	{
		DrawStuff(i);
	}
	if (mBox)
	{
		//printf("mBox = true \n");
		mBox = false;
		if (mBoxCount != BOX_MAX)
		{
			printf("mBox Count: %d \n",(mBoxCount+1));
			AddRect();
			mBoxCount++;
		}
	}
	//Update screen
	SDL_RenderPresent( mRenderer );

	return 0;
}



 /**
  * Loads the texture into mTexture
  * Uses LoadTexture from above
  */
 int GameData::LoadMedia() 
 {
	 //Load PNG texture 
	 if(( mTexture = LoadTexture( "Image/Right.png" )) == NULL ) 
	 { 
		 printf( "Failed to load texture image!\n" ); 
		 return -1;
	 }
	 if ((mChar = LoadTexture("Image/Char.png" )) == NULL)
	 {
		 printf( "Failed to load texture image!\n" ); 
		 return -1;
	 }
	 if ((mGround = LoadTexture("Image/Ground.png" )) == NULL)
	 {
		 printf( "Failed to load texture image!\n" ); 
		 return -1;
	 }
	 return 0;
 }

 /**
  *Gets input from user
  *Quits if quit button is pressed
  */
int GameData::Input()
{
	SDL_Event e;
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT){
		mDone = true;
	} else if (e.type == SDL_KEYDOWN)
	{
		switch(e.key.keysym.sym)
		{
		case SDLK_SPACE:
			mVelY += mJump;
			printf("Jump \n");
			break;
		case SDLK_a:
			mVelX -= CHAR_SPEED;
			printf("Left \n");
			break;
		case SDLK_d:
			mVelX += CHAR_SPEED;
			printf("Right \n");
			break;
		case SDLK_m:
			mBox = true;
			if (mBoxCount != BOX_MAX) printf("New Box \n");
			else printf("Max Boxes reached \n");
			break;
		default:
			printf("Nothing \n");
			break;
		};
		mChanged = true;
	}
	return 0;
}

/**
 *Moves the Character based on grav, position, input, and floor
 *
 */
int GameData::Move(){
	//X Velocity Control
	mCharX += mVelX;
	if  (( mCharX < 0 ) || ( mCharX + CHAR_WIDTH > SCREEN_WIDTH ) )
	{
		mCharX -= mVelX;
		mVelX = 0;
	}
	
	// Y Velocity Control
	if (mCharY > 0)
	{
		mCharY += mVelY;
	}
	if (mCharY + CHAR_WIDTH + 50 < SCREEN_HEIGHT)
	{
		mVelY += mGrav;
	}
	if  (( mCharY < 0 ) || ( mCharY + CHAR_WIDTH + 50 > SCREEN_HEIGHT ) )
	{
		mCharY += mVelY;
		mVelY = 0;
	}

	return 0;
}

/**
 * Update the characters position
 * Calls Move() if character is moving.
 */
int GameData::Update()
{
	if (mVelX != 0 || mVelY != 0)
	{
		Move();
		mChanged = false;
		return -1;
	}

	return 0;
}

/**
 *Main game loop
 *Gets input and updates/draws
 */

int GameData::Run()
{
	do
	{
		Input();
		if (Update() < 0 || mChanged)
		{
			Draw();
		}
		SDL_Delay(SDL_DELAY);
	}while(!mDone);

	return 0;
}