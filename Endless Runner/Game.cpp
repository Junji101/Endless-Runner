#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Game.h"

const int SDL_DELAY = 10;
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
const int CHAR_HEIGHT = 50;
const int CHAR_WIDTH = 50;
const int CHAR_SPEED = 3;
	
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

/**
 * Draw a platform
 * Future: Draw Objects
 */
int GameData::DrawStuff()
{
	SDL_Rect fillRect = { SCREEN_WIDTH/2 , (SCREEN_HEIGHT-200), 500, 50};
	//SDL_SetRenderDrawColor( mRenderer, 0x00, 0xFF, 0x00, 0xFF ); 
	//SDL_RenderFillRect( mRenderer, &fillRect );
	SDL_RenderCopy( mRenderer, mGround, NULL, &fillRect);
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
	SDL_RenderCopy( mRenderer, mTexture, NULL, NULL ); 
	//Update screen
	DrawFloor();
	DrawChar();
	DrawStuff();
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


int GameData::Update()
{
	if (mVelX > 0 || mVelY > 0)
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
		if (Update() < 0)
		{
			Draw();
		}
		SDL_Delay(SDL_DELAY);
	}while(!mDone);

	return 0;
}