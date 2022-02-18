// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <iostream>
#include <string>
#include<map>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum Img_Key{GUITAR, BELLS, DRUM, CRASH};

int main(int argc, char* args[])
{
	SDL_Window* myWindow = NULL;
	SDL_Texture* newTexture = NULL;
	SDL_Renderer* theRenderer = NULL;
	Mix_Music* gCasio = NULL;
	Mix_Chunk* gScratch = NULL;
	Mix_Chunk* gHigh = NULL;
	Mix_Chunk* gMedium = NULL;
	Mix_Chunk* gLow = NULL;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
	string imageFile = "HelloSDL.png";
	SDL_Surface* theSurface = IMG_Load(imageFile.c_str());
	newTexture = SDL_CreateTextureFromSurface(theRenderer, theSurface);
	
	map<Img_Key,SDL_Texture*> imgInstrument;
	imgInstrument[GUITAR] = SDL_CreateTextureFromSurface(theRenderer,IMG_Load("Guitar.png"));
	imgInstrument[BELLS] = SDL_CreateTextureFromSurface(theRenderer,IMG_Load("Bells.png"));
	imgInstrument[DRUM] = SDL_CreateTextureFromSurface(theRenderer,IMG_Load("Drum.png"));
	imgInstrument[CRASH] = SDL_CreateTextureFromSurface(theRenderer,IMG_Load("Crash.png"));


	SDL_FreeSurface(theSurface);
	gCasio = Mix_LoadMUS("Casio.wav");
	gScratch = Mix_LoadWAV("Guitar.wav");
	gHigh = Mix_LoadWAV("Bells.wav");
	gMedium = Mix_LoadWAV("Drum.wav");
	gLow = Mix_LoadWAV("Crash.wav");


	bool Done = false;
	SDL_Event e;

	while (!Done)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				Done = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					//Play high sound effect
				case SDLK_1:
					Mix_PlayChannel(-1, gHigh, 0);
					newTexture = imgInstrument[BELLS];
					break;

					//Play medium sound effect
				case SDLK_2:
					Mix_PlayChannel(-1, gMedium, 0);
					newTexture = imgInstrument[DRUM];
					break;

					//Play low sound effect
				case SDLK_3:
					Mix_PlayChannel(-1, gLow, 0);
					newTexture = imgInstrument[CRASH];
					break;

					//Play scratch sound effect
				case SDLK_4:
					Mix_PlayChannel(-1, gScratch, 0);
					newTexture = imgInstrument[GUITAR];
					break;

				case SDLK_9:
					//If there is no music playing
					if (Mix_PlayingMusic() == 0)
					{
						//Play the music
						Mix_PlayMusic(gCasio, -1);
					}
					//If music is being played
					else
					{
						//If the music is paused
						if (Mix_PausedMusic() == 1)
						{
							//Resume the music
							Mix_ResumeMusic();
						}
						//If the music is playing
						else
						{
							//Pause the music
							Mix_PauseMusic();
						}
					}
					break;

				case SDLK_0:
					//Stop the music
					Mix_HaltMusic();
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(theRenderer);
		SDL_RenderCopy(theRenderer,newTexture,NULL,NULL);
		SDL_RenderPresent(theRenderer);
	}
	Mix_FreeChunk(gScratch);
	Mix_FreeChunk(gHigh);
	Mix_FreeChunk(gMedium);
	Mix_FreeChunk(gLow);
	gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;

	//Free the music
	Mix_FreeMusic(gCasio);
	gCasio = NULL;
	SDL_DestroyTexture(newTexture);
	newTexture = NULL;
	for(auto& [name,tx]:imgInstrument){
		SDL_DestroyTexture(tx);
		tx = NULL;
	}

	SDL_DestroyRenderer(theRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	theRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
	return 0;
}