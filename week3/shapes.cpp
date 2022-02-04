#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <string>
#include<cmath>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void drawCircle( int cx, int cy, int radius, bool filled, SDL_Renderer* theRenderer){
    auto drawCircleBorder = [&](int r){
        for(double theta=0;theta<=2*M_PI;theta+=0.005){
            double x = cx + r * cos(theta);
            double y = cy + r * sin(theta);
            SDL_RenderDrawPoint(theRenderer,  x, y);
        }
    };
    if(!filled) drawCircleBorder(radius);
    else while(--radius) drawCircleBorder(radius);
}

int main(int argc, char* args[])
{
	SDL_Window* myWindow = NULL;
	SDL_Texture* newTexture = NULL;
	SDL_Renderer* theRenderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	
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
		SDL_SetRenderDrawColor(theRenderer, 0x00, 0x00, 0x00, 0xFF);

        // HERE!!!
        drawCircle(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,100,true,theRenderer);
		SDL_RenderPresent(theRenderer);
        
        
        SDL_Delay(32);
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