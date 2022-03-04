#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_ttf.h"
#include<string>
struct Vector2
{
	float x;
	float y;
};

struct Tex{
	SDL_Texture* tex;
	int width;
	int height;
};

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	
	bool mIsRunning;
	int mPaddleDir;
	Vector2 mPaddlePos;
	Vector2 mBallPos;
	Vector2 mBallVel;

	Tex paddleTex,ballTex;

	void loadFromFile(std::string path, Tex& tex );

	short int bgCol[2][3] = {{0, 155 ,0}, {155 , 0, 0}};
	bool bgTurn = 0;

	TTF_Font* theFont = NULL;

	Mix_Chunk* hitSound = NULL;
	Mix_Music* bgmSound = NULL;

	int bestScore = 0;
	int score=0;
	

};
