#include <SDL.h>
#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* args[])
{
	SDL_Window* myWindow = nullptr;
	SDL_Surface* myScreenSurface = nullptr;
	SDL_Surface* HelloSDLSurface = nullptr;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL Init failed" << SDL_GetError() << endl;
	}
	else
	{
		myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, WIDTH, HEIGHT, 0);
		if (myWindow == nullptr)
		{
			cout << "Create Window failed " << SDL_GetError() << endl;
		}
		else
		{
			myScreenSurface = SDL_GetWindowSurface(myWindow);
			HelloSDLSurface = SDL_LoadBMP("HelloSDL.bmp");
			if (HelloSDLSurface == nullptr)
			{
				cout << "Unable to load " << "HelloSDL.bmp" << SDL_GetError() << endl;
			}
			else
			{
				bool Done = false;

				SDL_Event eve;
				while (!Done)
				{
					while (SDL_PollEvent(&eve) != 0)
					{
						if (eve.type == SDL_QUIT)
						{
							Done = true;
						}
					}

					SDL_BlitSurface(HelloSDLSurface, NULL, myScreenSurface, NULL);
					SDL_UpdateWindowSurface(myWindow);
				}
			}
		}
	}
	SDL_FreeSurface(HelloSDLSurface);
	HelloSDLSurface = nullptr;
	SDL_FreeSurface(HelloSDLSurface);
	HelloSDLSurface = nullptr;
	SDL_DestroyWindow(myWindow);
	myWindow = nullptr;
	SDL_Quit();
	return 0;
}