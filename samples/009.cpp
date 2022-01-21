#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	SDL_Window* myWindow = NULL;
	SDL_Texture* newTexture = NULL;
	SDL_Renderer* theRenderer = NULL;
	TTF_Font* theFont = NULL;
	int mWidth;
	int mHeight;

	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	TTF_Init();

	theFont = TTF_OpenFont("Dubai-Regular.ttf", 28);
		
	SDL_Color textColor = { 0, 0, 0 };
	string textureText = "Welcome to the Hotel California, such a lovely place!";

	SDL_Surface* textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
	newTexture = SDL_CreateTextureFromSurface(theRenderer, textSurface);
		
	mWidth = textSurface->w;
	mHeight = textSurface->h;

	SDL_FreeSurface(textSurface);

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
		}
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(theRenderer);

		int x = (SCREEN_WIDTH - mWidth) / 2;
		int y = (SCREEN_HEIGHT - mHeight) / 2;
		SDL_Rect* clip = NULL;
		double angle = 45;

			
		SDL_Rect renderQuad = { x, y, mWidth, mHeight };

		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		
		SDL_RenderCopyEx(theRenderer, newTexture, clip, &renderQuad, angle, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(theRenderer);
	}

	SDL_DestroyTexture(newTexture);
	newTexture = NULL;

	SDL_DestroyRenderer(theRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	theRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
	return 0;
}