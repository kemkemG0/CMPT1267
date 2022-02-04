#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
	
	int textureWidth;
	int textureHeight;

	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	
	string imageFile = "arrow.png";
	SDL_Surface* theSurface = IMG_Load(imageFile.c_str());
	newTexture = SDL_CreateTextureFromSurface(theRenderer, theSurface);
		
	textureWidth = theSurface->w;
	textureHeight = theSurface->h;

	SDL_FreeSurface(theSurface);

	bool Done = false;
	SDL_Event e;
	double degrees = 0;
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
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
					case SDLK_a:
						degrees -= 60;
						break;

					case SDLK_s:
						degrees += 60;
						break;

					case SDLK_q:
						flipType = SDL_FLIP_HORIZONTAL;
						break;

					case SDLK_w:
						flipType = SDL_FLIP_NONE;
						break;

					case SDLK_e:
						flipType = SDL_FLIP_VERTICAL;
						break;
				}
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(theRenderer);

		//Render arrow
		int x = (SCREEN_WIDTH - textureWidth) / 2;
		int y = (SCREEN_HEIGHT - textureHeight) / 2;
		SDL_Rect* clip = NULL;
		SDL_Rect renderQuad = { x, y, textureWidth, textureHeight };
		//Set clip rendering dimensions
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}
		//Render to screen
		SDL_RenderCopyEx(theRenderer, newTexture, clip, &renderQuad, degrees, NULL, flipType);
		//Update screen
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