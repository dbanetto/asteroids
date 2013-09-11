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

enum SHIP_CONTROLLER {
     //Ship controlled by a Local player
     SHIP_CONTOLLER_PLAYER,
     //Ship is controlled by a player which is connected over a network
     SHIP_CONTOLLER_NETWORK,
     //Ship is controlled by an AI
     SHIP_CONTOLLER_AI
};

class Ship : public sprite {
public:
     Ship(SHIP_CONTROLLER controller);
     virtual ~Ship();

     int generateTexture(SDL_Renderer* render);
     virtual void render (double delta , SDL_Renderer* rednerer);
     virtual void update (double delta);


     double getAngle(void);
     void   setAngle(double angle);



protected:
     std::vector<SDL_Point> render_points;

     std::vector<SDL_Point> boundary_points;
     std::vector<SDL_Point> boundary_points_rotated;

     SDL_Point center;
     SHIP_CONTROLLER controller;
     //Angle measured in degrees
     double angle;

private:
          SDL_Texture* texture;
          bool RENDER_TEXTURE;
          bool UPDATE_ROTATION;
};

#endif /* SHIP_H_ */
