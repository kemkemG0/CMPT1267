#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include<vector>


using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
	
	vector<string> imageFiles = {"arrow.png","rust.png","go.png"};
    vector<SDL_Texture*> textures;
    vector<pair<int,int>> WH;
    for(string path:imageFiles){
        auto surface = IMG_Load(path.c_str());
    	auto tex = SDL_CreateTextureFromSurface(theRenderer, surface);
        WH.push_back({
            surface->w,
            surface->h
        });
        textures.push_back(tex);
	    SDL_FreeSurface(surface);
    }
	newTexture = textures[0];

	bool Done = false;
	SDL_Event e;
	double degrees = 0;
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
    int ind = 0;
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

                    case SDLK_m:
                        ind++,ind%=3;
                        break;
                    case SDLK_n:
                        ind =0;
                        break;
				}
			}
		}
        newTexture = textures[ind];

		//Clear screen
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(theRenderer);

        auto [width,height] = WH[ind];
		//Render arrow
		int x = (SCREEN_WIDTH - width) / 2;
		int y = (SCREEN_HEIGHT - height) / 2;
		SDL_Rect* clip = NULL;
		SDL_Rect renderQuad = { x, y, width, height };
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