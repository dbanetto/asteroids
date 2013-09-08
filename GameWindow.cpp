/*
 * GameWindow.cpp
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#include "GameWindow.h"
#include <iostream>
#include "util/Timer.h"
#include <sstream>

#include "render/Ship.h"

Ship player = Ship(SHIP_CONTOLLER_PLAYER);

GameWindow::GameWindow() {
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1) {
			std::cout << "An error has occurred" << std::endl;
			std::cerr << SDL_GetError() << std::endl;
			return;
	}
	TTF_Init();
	//Has not been inited, yet
	this->inited = false;

	//Pointer safety
	this->window   = nullptr;
	this->renderer = nullptr;

	this->quit = false;

	this->CAP_FPS = true;
	this->FPS_MAX = 60;
	this->CURRENT_FPS = 0;

	this->title = nullptr;
	this->width = 800;
	this->hieght = 600;
	this->SDL_SCREEN_FLAGS = SDL_INIT_EVERYTHING;
}

GameWindow::~GameWindow() {
	// TODO Auto-generated destructor stub
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	TTF_Quit();
	SDL_Quit();
}

/// <summary>
/// Initializes the Game Window.
/// </summary>
/// <param name="TITLE">The title.</param>
/// <param name="WIDTH">The width of the window.</param>
/// <param name="HIEGHT">The height of the window.</param>
/// <param name="Background">The background colour.</param>
/// <param name="SDL_SCREEN_FLAGS">SDL_SCREEN_FLAGS.</param>
/// <returns></returns>
int GameWindow::Init(const char* TITLE ,int WIDTH, int HIEGHT , SDL_Color Background , int SDL_SCREEN_FLAGS )
{
    this->background = Background;
    this->title = TITLE;
    this->width = WIDTH;
    this->hieght = HIEGHT;
    this->SDL_SCREEN_FLAGS = SDL_SCREEN_FLAGS;

    //Create Window
    this->window = SDL_CreateWindow (this->title , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->hieght , SDL_SCREEN_FLAGS );
    //Make sure it was created correctly
    if (this->window == nullptr) {
    	std::cout << "An error has occurred" << std::endl;
		std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    //Create Renderer
    this->renderer = SDL_CreateRenderer (this->window , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC  );
    //Make sure it was created correctly
    if (this->renderer == nullptr) {
    	std::cout << "An error has occurred" << std::endl;
		std::cerr << SDL_GetError() << std::endl;
        return 1;
    }
    this->inited = true;
    player.generateTexture(this->renderer);
    return 0;
}

void GameWindow::Start() {
	//Update Thread
	    Timer fps = Timer();

	    Timer delta = Timer();

	    //Frame rate counter
	    Timer counter = Timer();
	    int counter_frames = 0;

	    //Start Counter
	    counter.start();

	    //Start Delta
	    delta.start();
	    while (!this->quit) {  //While not quitting, UPDATE!
	    	//Start counting frame time for capping
			fps.start();

			//RENDERS HERE
			this->Render(delta.get_ticks());
			this->Update(delta.get_ticks());
			//Restart Delta
			delta.start();
			//Reset background colour
			SDL_SetRenderDrawColor(this->renderer, this->background.r, this->background.g, this->background.b, this->background.a);
			//Copy back buffer to Screen
			SDL_RenderPresent(this->renderer);
			SDL_RenderClear  (this->renderer);

			//Mid Render Check for exit
			if (this->quit)
				break;

			//Increment frame count
			counter_frames++;

			//Check if Capping is needed
			if( this->CAP_FPS && ( fps.get_ticks() < 1000 / this->FPS_MAX ) ) //If time less then allocated
			{
				//Sleep the remaining allocated frame time
				SDL_Delay( ( 1000 / this->FPS_MAX ) - fps.get_ticks() );
			}

			if (counter.get_ticks() > 1000) { //1 second worth of frames collected
				this->CURRENT_FPS = counter_frames / ( counter.get_ticks() / 1000.f );

				counter.start();
				counter_frames = 0;
			}
	    }
}

void GameWindow::Render(int delta) {
	player.render(delta , renderer);
}

void GameWindow::Update(int delta) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		this->Event(event);
	}
	//Update Title
	std::stringstream ss;
	ss << "Asteroids @ " << this->CURRENT_FPS << "fps";
	SDL_SetWindowTitle(this->window , ss.str().c_str());
}

void GameWindow::Event (SDL_Event e)
{
    switch (e.type) {
        case (SDL_QUIT):
            this->quit = true;
            break;
        case (SDL_KEYDOWN):
            if (e.key.keysym.sym == SDLK_ESCAPE)
            	this->quit = true;
            break;
    }
}

