/*
 * sprite.h
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDL2/SDL.h"
#include <vector>

class sprite {
public:
     sprite();
     virtual ~sprite();
     virtual void render (int delta , SDL_Renderer* rednerer);
     virtual void update (int delta);

     SDL_Rect getBounds(void);
     void setBounds(SDL_Rect rect);

     SDL_Point getPosition(void);
     void setPosition(SDL_Point pos);

protected:
     SDL_Rect bounds;
};

std::vector<SDL_Point> rotate (std::vector<SDL_Point> points, SDL_Point center , double angleDeg);
void rotate (std::vector<SDL_Point>* points, SDL_Point center , double angleDeg);

bool isPointInsidePolygon(SDL_Point pt , std::vector<SDL_Point>* polygon);

#endif /* SPRITE_H_ */
