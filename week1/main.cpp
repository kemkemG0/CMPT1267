#include <SDL.h>
#include <iostream>
using namespace std;


const int WIDTH = 800;
const int HEIGHT = 600;
int main(int argc, char* args[]){
	SDL_Window* window=nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Surface* HelloSDLSurface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL_Init failed, Error: " << SDL_GetError()<<endl;
	}
	else
	{
		window = SDL_CreateWindow("CMPT 1267", 100, 100, WIDTH, HEIGHT, 0);
		if (window == nullptr)
		{
			cout << "SDL_CreateWindow failed, Error: " << SDL_GetError() << endl;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			HelloSDLSurface = SDL_LoadBMP("HelloSDL.bmp");
			if (HelloSDLSurface == nullptr)
			{
				cout << "I couldn't open the file" << endl;
			}
			else
			{
				SDL_BlitSurface(HelloSDLSurface, NULL, screenSurface, NULL);
				SDL_UpdateWindowSurface(window);
                // A basic main loop to prevent blocking
				bool is_running = true;
                SDL_Event event;
                while (is_running) {
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            is_running = false;
                        }
						else if(event.type==SDL_KEYDOWN){
							if(event.key.keysym.sym==SDLK_0){
								is_running=false;
							}
						}
                    }
                    SDL_Delay(16);
                }
			}
		}
	}
	SDL_FreeSurface(HelloSDLSurface);
	HelloSDLSurface = nullptr;
	SDL_FreeSurface(screenSurface);
	screenSurface = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();

	return 0;
}