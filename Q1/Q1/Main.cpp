#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <assert.h>
#include <iostream>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window* myWindow = NULL;
SDL_Texture* strTexture = NULL;
SDL_Renderer* theRenderer = NULL;
TTF_Font* theFont = NULL;
SDL_Surface* textSurface = NULL;



void drawLines() {
	SDL_SetRenderDrawColor(theRenderer, 0x00, 0x00, 0, 0xFF);
	SDL_RenderDrawLine(theRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	SDL_RenderDrawLine(theRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
}

void drawText(int type) {
	string textureText = "test";

	int topX = 0, topY=0;
	if (type == 1) {
		topX = topY = 0;
		textureText = "One";
	}else if(type == 2) {
		topX = SCREEN_WIDTH / 2;
		textureText = "Two";
	}else if(type == 3) {
		topY = SCREEN_HEIGHT / 2;
		textureText = "Three";
	}else if(type == 4) {
		topX = SCREEN_WIDTH / 2;
		topY = SCREEN_HEIGHT / 2;
		textureText = "Four";
	}
	else {
		assert(false);
	}
	topX -= 50;
	topY -= 50;

	SDL_Rect board{
		topX+SCREEN_WIDTH/4,//topx
		topY + SCREEN_HEIGHT/4,//topy
		100,
		75,
	};

	textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), { 0,0,0 });
	 strTexture = SDL_CreateTextureFromSurface(theRenderer, textSurface);
	SDL_FreeSurface(textSurface);

	SDL_RenderCopy(theRenderer, strTexture, NULL, &board);
}





int main(int argc, char* args[])
{
	

	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	theFont = TTF_OpenFont("Dubai-Regular.ttf", 28);

	bool Done = false;
	bool isDraw = true;
	SDL_Event e;
	int textType = 1;
	while (!Done)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			std::cout<<"a\n";
			if (e.type == SDL_QUIT)
			{
				Done = true;
			}
			if (e.type == SDL_KEYDOWN) {
				// when key pressed
				auto key = e.key.keysym.sym;
				if (key == SDLK_1) {
					textType = 1;
					isDraw = true;
				}
				else if (key == SDLK_2) {
					textType = 2;
					isDraw = true;
				}
				else if (key == SDLK_3) {
					textType = 3;
					isDraw = true;
				}
				else if (key == SDLK_4) {
					textType = 4;
					isDraw = true;
				}
				else isDraw = false;
					 
			}
		}
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(theRenderer);

		if (isDraw) {
			drawLines();
			drawText(textType);
		}


		SDL_RenderPresent(theRenderer);
		SDL_DestroyTexture(strTexture);
	}

	if(strTexture!=NULL)SDL_DestroyTexture(strTexture);
	strTexture = NULL;

	SDL_DestroyRenderer(theRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	theRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	return 0;
}