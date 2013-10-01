/*
 * GameWindow.h
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "render/sprite.h"
#include "util/Camera.h"

class GameWindow
{
public:
    GameWindow();
    virtual ~GameWindow();

    int Init(const char* TITLE ,int WIDTH, int HIEGHT , SDL_Color BACKGROUND_COLOUR ,  int SDL_SCREEN_FLAGS );

    void Start(void);
protected:
    void Render(double delta);
    void Update(double delta);
    void Event (SDL_Event e , double delta);
    void centerVeiwPortOnSprite(sprite* sp);
private:
    //Private variables
    SDL_Renderer* renderer;
    SDL_Window*   window;
    bool inited, quit;

    //Viewport
    Camera camera;

    //Enabled/Disabled capping
    bool CAP_FPS;

    //maximum Frames per second Cap
    int FPS_MAX;

    int CURRENT_FPS;
    double GAMETIME_MULTIPLIER;
    //init options
    const char* title = nullptr;
    int SDL_SCREEN_FLAGS;
    SDL_Color background;

};



#endif /* GAMEWINDOW_H_ */
