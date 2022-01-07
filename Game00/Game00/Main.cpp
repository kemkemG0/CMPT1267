#include<SDL.h>
#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "SDL Init failed! SDL_Error: " << SDL_GetError() << endl;
	else
	{
		window = SDL_CreateWindow("CMPT 1267", 100, 100, WIDTH, HEIGHT, 0);
		if (window == nullptr)
			cout << "Create Window failed! SDL_Error: " << SDL_GetError() << endl;
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			auto Hello = SDL_LoadBMP("file");
			
			SDL_UpdateWindowSurface(window);
			// A basic main loop to prevent blocking
			bool is_running = true;
			SDL_Event event;
			while (is_running) {
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						is_running = false;
					}
				}
				SDL_Delay(16);
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