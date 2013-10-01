/*
 * Ship.h
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#ifndef SHIP_H_
#define SHIP_H_
#include <vector>
#include "SDL2/SDL.h"
#include "sprite.h"

enum SHIP_CONTROLLER
{
    //Ship controlled by a Local player
    SHIP_CONTOLLER_PLAYER,
    //Ship is controlled by a player which is connected over a network
    SHIP_CONTOLLER_NETWORK,
    //Ship is controlled by an AI
    SHIP_CONTOLLER_AI
};

class Ship : public sprite
{
public:
    Ship(SHIP_CONTROLLER controller);
    virtual ~Ship();

    void generateTexture(SDL_Renderer* renderer);
    virtual void render (double delta , SDL_Renderer* rednerer , SDL_Point CameraOffset);
    virtual void update (double delta);


protected:
    std::vector<SDL_Point> render_points;

    std::vector<SDL_Point> boundary_points;
    SHIP_CONTROLLER controller;
    //Angle measured in degrees

private:
    SDL_Texture* texture;
    bool RENDER_TEXTURE;
};

#endif /* SHIP_H_ */
