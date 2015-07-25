#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Game.h"

const int SDL_DELAY = 10;
/**
 *Sets up the loading of SDL
 *Creates window, renderer, and img flags
 */
int GameData::Setup()
{
	if (SDL_Init( SDL_INIT_EVERYTHING ) < 0)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		return -1;
	}

	if ((mWindow = SDL_CreateWindow("Hello World",0,100,800,800,0)) == NULL)
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

int GameData::DrawBackG()
{
	SDL_RenderClear();



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
	SDL_RenderPresent( mRenderer );
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
  * Loads the texture into mTexture
  * Uses LoadTexture from above
  */
 int GameData::LoadMedia() 
 {
	 //Load PNG texture 
	 mTexture = LoadTexture( "Image/Right.png" ); 
	 if( mTexture == NULL ) 
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
		Draw();
		SDL_Delay(SDL_DELAY);
	}while(!mDone);

	return 0;
}