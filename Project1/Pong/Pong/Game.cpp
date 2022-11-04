#include "Game.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
{
	mWindow=nullptr;
	mRenderer=nullptr;
	mTicksCount=0;
	mIsRunning=true;
	mPaddleDir=0;

	paddleTex.tex = ballTex.tex =  nullptr;
}

void Game::loadFromFile(std::string path, Tex& tex )
{
	if (tex.tex != NULL)
	{
		SDL_DestroyTexture(tex.tex);
		tex.tex = NULL;
	}
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	tex.tex = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);

	if (loadedSurface != nullptr)
	{
		tex.width = loadedSurface->w;
		tex.height = loadedSurface->h;
	}
	else
	{
		printf("Error! Cannot Load the Image!!");
		SDL_FreeSurface(loadedSurface);
	}
}


bool Game::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"CMPT 1267", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f/2.0f;
	mBallPos.x = 1024.0f/2.0f;
	mBallPos.y = 768.0f/2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

	IMG_Init(IMG_INIT_PNG);
	loadFromFile("ball.png", ballTex);
	loadFromFile("go.png", paddleTex);


	// Load files
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	hitSound = Mix_LoadWAV("hit.wav");
	bgmSound = Mix_LoadMUS("bgm.wav");
	Mix_PlayMusic(bgmSound,-1);
	
	TTF_Init();

	theFont = TTF_OpenFont("Dubai-Regular.ttf", 28);
	if(theFont==nullptr){
        std::cout<<"This ttf file does not exist."<<std::endl;
        return 1;
    }
	
	std::ifstream input("bestscore.txt");
	input>> bestScore;
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
		if(event.type==SDL_KEYDOWN){
			switch (event.key.keysym.sym){
				case SDLK_z:
					if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
					else Mix_PauseMusic();
				break;
			}
		}
	}
	
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	
	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void Game::UpdateGame(){
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	
	// Update paddle position based on direction
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (paddleH/2.0f + thickness))
		{
			mPaddlePos.y = paddleH/2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH/2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH/2.0f - thickness;
		}
	}
	
	// Update ball position based on ball velocity
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;
	
	// Bounce if needed
	// Did we intersect with the paddle?
	float diff = mPaddlePos.y - mBallPos.y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
		bgTurn = !bgTurn;//change the flag of color
		Mix_PlayChannel(-1, hitSound, 0);
		++score;
	}
	// Did the ball go off the screen? (if so, end game)
	else if (mBallPos.x <= 0.0f)
	{
		mIsRunning = false;
	}
	// Did the ball collide with the right wall?
	else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	
	// Did the ball collide with the top wall?
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (mBallPos.y >= (768 - thickness) &&
		mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
}

void Game::GenerateOutput()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		bgCol[bgTurn][0],		// R
		bgCol[bgTurn][1],		// G 
		bgCol[bgTurn][2],	    // B
		255		// A
	);
	
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 200, 200, 0, 255);
	
	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);
	
	// Draw ball
	SDL_Rect newBall;  
	newBall.x = mBallPos.x - thickness / 2;
	newBall.y = mBallPos.y - thickness / 2;
	newBall.h = thickness + 15;
	newBall.w = thickness + 15;
	SDL_RenderCopy(mRenderer, ballTex.tex, NULL, &newBall);


	// Draw paddle
	// Draw ball
	SDL_Rect newPaddle;
	newPaddle.x = mPaddlePos.x;
	newPaddle.y = mPaddlePos.y - paddleH/2,
	newPaddle.w = thickness,
	newPaddle.h = paddleH;
	SDL_RenderCopy(mRenderer, paddleTex.tex, NULL, &newPaddle);


	auto currentScoreTex = SDL_CreateTextureFromSurface(
		mRenderer, 
		TTF_RenderText_Solid(theFont, std::string("Score:"+ std::to_string(score) ).c_str(), { 0, 0, 0 })
		);
	auto bestScoreTex = SDL_CreateTextureFromSurface(
		mRenderer, 
		TTF_RenderText_Solid(theFont, std::string("BestScore:"+ std::to_string(bestScore) ).c_str(), { 0, 0, 0 })
		);
	SDL_Rect currentScore;
	currentScore.x = 600;
	currentScore.y = 50;
	currentScore.w = 150,
	currentScore.h = 90;
	SDL_RenderCopy(mRenderer, currentScoreTex, NULL, &currentScore);

	SDL_Rect bestScoreRect;
	bestScoreRect.x = 600;
	bestScoreRect.y = 140;
	bestScoreRect.w = 200,
	bestScoreRect.h = 90;
	SDL_RenderCopy(mRenderer, bestScoreTex, NULL, &bestScoreRect);
	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void destroyTextures(Tex& tex){
	if (tex.tex != NULL)
	{
		SDL_DestroyTexture(tex.tex);
		tex.tex = NULL;
	}
}

void Game::Shutdown()
{
	std::ofstream out("bestScore.txt");
	out << std::max(bestScore,score);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mRenderer = nullptr;
	mWindow = nullptr;
	//Free loaded images
	destroyTextures(ballTex);
	destroyTextures(paddleTex);
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}