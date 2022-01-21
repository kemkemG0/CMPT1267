#include <SDL.h>
#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* args[]){
    SDL_Window* window=nullptr;
    SDL_Surface* screenSurface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "SDL_Init failed, Error: " << SDL_GetError()<<endl;
	}
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
                    else if(event.type==SDL_KEYDOWN){
                        switch (event.key.keysym.sym){
                            case SDLK_r:
                                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 0, 0)); 
                                break;
                            case SDLK_g:
                                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 255, 0)); 
                                break;
                            case SDLK_b:
                                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 255)); 
                                break;
                            case SDLK_y:
                                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 255, 0)); 
                                break;
                            case SDLK_q:
                                is_running = false;
                                break;
                            default:
                                break;
                        }
                        SDL_UpdateWindowSurface(window);
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