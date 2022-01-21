#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* args[])
{
	SDL_Window* myWindow = nullptr;
	SDL_Texture* newTexture = nullptr;
	SDL_Renderer* theRenderer = nullptr;

	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, 640, 480, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);

	SDL_Surface* loadedSurface = IMG_Load("test.png");
	if (loadedSurface == nullptr)
	{
			cout << "Unable to load image" << endl;
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(theRenderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
		loadedSurface = nullptr;

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
			SDL_RenderClear(theRenderer);
			SDL_RenderCopy(theRenderer, newTexture, NULL, NULL);
			SDL_RenderPresent(theRenderer);
		}

		SDL_DestroyRenderer(theRenderer);
		theRenderer = nullptr;
		SDL_DestroyTexture(newTexture);
		newTexture = nullptr;
		SDL_DestroyWindow(myWindow);
		myWindow = nullptr;
		IMG_Quit();
		SDL_Quit();
	}
	return 0;
}