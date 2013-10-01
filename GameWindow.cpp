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
#include "render/PlayerShip.h"
#include "render/Asteroid.h"
#include <cfloat>
#include "util/vector.h"
#include <vector>
#include "util/AreaMap.h"
#include "util/area.h"
#include "io/Settings.h"
#include <stdlib.h>

PlayerShip player;

std::vector<Asteroid> sprites;
AreaMap sprite_map;

Settings settings;

GameWindow::GameWindow()
{
    if ( SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout << "An error has occurred" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return;
    }
    TTF_Init();
    //Has not been inited, yet
    this->inited = false;
    this->GAMETIME_MULTIPLIER = 1.0;
    //Pointer safety
    this->window   = nullptr;
    this->renderer = nullptr;

    this->quit = false;
    this->CAP_FPS = true;
    this->FPS_MAX = 60;
    this->CURRENT_FPS = 0;

    this->title = nullptr;
    SDL_Rect viewport;
    viewport.w = 800;
    viewport.h = 600;
    this->camera = Camera( viewport );
    this->SDL_SCREEN_FLAGS = SDL_INIT_EVERYTHING;


    settings.open (SETTINGS_LOCATION);
}

GameWindow::~GameWindow()
{
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
    settings.load(0);

    this->background = Background;
    this->title = TITLE;
    SDL_Rect viewport;
    viewport.w = WIDTH;
    viewport.h = HIEGHT;
    this->camera = Camera( viewport );


    this->SDL_SCREEN_FLAGS = SDL_SCREEN_FLAGS;
    //Get window settings
    //Check if fullscreen is enabled
    if (settings.getBool( "screen.fullscreen" ) )
    {
        this->SDL_SCREEN_FLAGS = this->SDL_SCREEN_FLAGS | SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    //Check if any extras are added
    if (settings.exists( "screen.additionalflags" ) )
    {
        int additionalflags = settings.getInt("screen.additionalflags");
        if (additionalflags != 0)
        {
            this->SDL_SCREEN_FLAGS |= additionalflags;
        }
    }

    if (settings.exists( "render.fps.max" ) )
    {
        this->FPS_MAX = settings.getInt("render.fps.max");
    }
    if (settings.exists( "render.fps.cap" ) )
    {
        this->CAP_FPS = settings.getBool("render.fps.cap");
    }

    if (settings.exists( "render.fps.max" ) ) {
    	this->FPS_MAX = settings.getInt("render.fps.max");
	}
    if (settings.exists( "render.fps.cap" ) ) {
		this->CAP_FPS = settings.getBool("render.fps.cap");
	}

    //Create Window
    this->window = SDL_CreateWindow (this->title
                                     , SDL_WINDOWPOS_UNDEFINED
                                     , SDL_WINDOWPOS_UNDEFINED
                                     , viewport.w
                                     , viewport.h
                                     , this->SDL_SCREEN_FLAGS );
    SDL_SetWindowMinimumSize( this->window ,640,480);

    //Make sure it was created correctly
    if (this->window == nullptr)
    {
        std::cout << "An error has occurred" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    //Renderer Settings

    //Create Renderer
    this->renderer = SDL_CreateRenderer (this->window , -1 , SDL_RENDERER_ACCELERATED );

    //Make sure it was created correctly
    if (this->renderer == nullptr)
    {
        std::cout << "An error has occurred" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }
    this->inited = true;

    sprites.reserve(100);
    unsigned int seed = SDL_GetTicks();
    srand( seed );
    Asteroid asrto;

    //WARNING if counter is a unsigned int BAD things happen
    for (int counter = 0; counter < sprites.capacity(); counter++)
    {
        srand( seed * counter );
        asrto = Asteroid();
        SDL_Rect astro_b;
        Point pt_astro;
        astro_b.w = (rand() * counter) % 64 + 32;
        astro_b.h = (rand() * counter) % 64 + 32;
        asrto.setBounds(astro_b);
        asrto.generatePoints();
        pt_astro.x = (rand() * counter) % 1600 - 800;
        pt_astro.y = (rand() * counter) % 1200 - 600;

        asrto.setPosition(pt_astro);

        sprites.push_back(asrto);
        ISprite* sp = static_cast<ISprite*> ( &sprites[counter] );
        sprite_map.insert(sp);
    }

    return 0;
}

void GameWindow::Start()
{
    SDL_SetRenderDrawColor(this->renderer, this->background.r, this->background.g, this->background.b, this->background.a);
    SDL_RenderClear  (this->renderer);
    SDL_RenderPresent(this->renderer);


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
    while (!this->quit)    //While not quitting, UPDATE!
    {
        //Start counting frame time for capping
        fps.start();

        //RENDERS HERE
        // change in time in seconds with game-time multiplier to edit game speed
        double s_delta = (((double)(delta.get_ticks()) * GAMETIME_MULTIPLIER) / 1000.0)  + DBL_MIN;
        this->Render(s_delta);

        SDL_SetRenderDrawColor(this->renderer, this->background.r, this->background.g, this->background.b, this->background.a);
        //Copy back buffer to Screen


        s_delta = (((double)(delta.get_ticks()) * GAMETIME_MULTIPLIER) / 1000.0)  + DBL_MIN;
        this->Update(s_delta);

        SDL_RenderPresent(this->renderer);
        SDL_RenderClear  (this->renderer);

        //Restart Delta
        delta.start();
        //Reset background colour


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

        if (counter.get_ticks() > 1000)   //1 second worth of frames collected
        {
            this->CURRENT_FPS = counter_frames / ( counter.get_ticks() / 1000.0 );

            counter.start();
            counter_frames = 0;
        }
    }
}

void GameWindow::Render(double delta)
{
    player.render(delta , renderer , this->camera.getCameraOffset());

    std::vector<ISprite*> render_sprites = sprite_map.getSpritesFromArea(this->camera.getViewPort());
    for (unsigned int i = 0; i < render_sprites.size(); i++ )
    {
        //Asteroid* a_ptr = static_cast<Asteroid *>(render_sprites[i]);
        render_sprites[i]->render(delta , renderer , this->camera.getCameraOffset());
    }
    render_sprites.clear();

}

void GameWindow::Update(double delta)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        this->Event(event , delta);
    }
    sprite_map.clear();
    for (unsigned int i = 0; i < sprites.size(); i++ )
    {
        sprites[i].update(delta);
        ISprite* sp = static_cast<ISprite*> ( &sprites[i] );
        sprite_map.insert(sp);
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    player.input(state,delta);
    player.update(delta);
    //Update Title
    std::stringstream ss;
    ss << "Asteroids @ " << this->CURRENT_FPS << "fps" << " (x" << this->GAMETIME_MULTIPLIER
       << ")" << " sprite count:" << sprites.size();
    SDL_SetWindowTitle(this->window , ss.str().c_str());


    camera.BoxMoveWithSprite(&player);
}

void GameWindow::Event (SDL_Event e , double delta)
{

    switch (e.type)
    {
    case (SDL_QUIT):
        this->quit = true;
        break;
    case (SDL_KEYDOWN):
        if (e.key.keysym.sym == SDLK_ESCAPE)
        {
            this->quit = true;
        }
        if (e.key.keysym.sym == SDLK_p)
        {
            this->GAMETIME_MULTIPLIER = 0.1;
        }
        if (e.key.keysym.sym == SDLK_l)
        {
            this->GAMETIME_MULTIPLIER = 1;
        }
        if (e.key.keysym.sym == SDLK_o)
        {
            this->GAMETIME_MULTIPLIER = 10;
        }
        if (e.key.keysym.sym == SDLK_m)
        {
            this->FPS_MAX = 120;
        }
        if (e.key.keysym.sym == SDLK_n)
        {
            this->FPS_MAX = 60;
        }
        break;
    case (SDL_WINDOWEVENT):
        if (e.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            SDL_Rect t = this->camera.getViewPort();
            t.w = e.window.data1;
            t.h = e.window.data2;
            this->camera.setViewPort(t);
        }
        break;

    }
}
