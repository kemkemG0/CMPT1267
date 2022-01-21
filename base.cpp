#include <SDL.h>
#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

/*
    loading BMP:
        HelloSDLSurface = SDL_LoadBMP("HelloSDL.bmp");
			if (HelloSDLSurface == nullptr)
			{
				cout << "Unable to load " << "HelloSDL.bmp" << SDL_GetError() << endl;
			}
*/

int main(int argc, char* args[]){
    SDL_Window* window=nullptr;
    SDL_Surface* screenSurface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) cout << "SDL_Init failed, Error: " << SDL_GetError() << endl;
	
    else{
		window = SDL_CreateWindow("CMPT 1267", 100, 100, WIDTH, HEIGHT, 0);
		if (window == nullptr){
			cout << "SDL_CreateWindow failed, Error: " << SDL_GetError() << endl;
		}
		else{
			screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 255));
            SDL_UpdateWindowSurface(window);
            bool is_running = true;
            SDL_Event event;
            while (is_running) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        is_running = false;
                    }
                }
            }
		}
	}
	SDL_FreeSurface(screenSurface);
	screenSurface = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
	return 0;
}