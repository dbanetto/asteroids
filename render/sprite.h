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
#include "../util/Point.h"

class sprite {
public:
     sprite();
     virtual ~sprite();
     virtual void render (double delta , SDL_Renderer* rednerer);
     virtual void update (double delta);
     virtual void event  (SDL_Event event, double delta);
     SDL_Rect getBounds(void);
     void setBounds(SDL_Rect rect);

     Point getPosition(void);
     void setPosition(Point pos);
     SDL_Point getCenter ();
     std::vector<SDL_Point>* getPointBounds ();

protected:
     SDL_Rect bounds;
     Point    position;
     SDL_Point center;
     std::vector<SDL_Point> point_bounds;
};

std::vector<SDL_Point> rotate (std::vector<SDL_Point> points, SDL_Point center , double angleDeg);
void rotate (std::vector<SDL_Point>* points, SDL_Point center , double angleDeg);

bool isPointInsidePolygon(SDL_Point pt , std::vector<SDL_Point>* polygon);
bool isPolygonInsidePolygon(std::vector<SDL_Point>* pt , std::vector<SDL_Point>* polygon);
bool isRectTouching (SDL_Rect* rect1, SDL_Rect* rect2);


bool isSpriteTouchingSprite (sprite sp1 , sprite sp2);


SDL_Texture* GenerateTextureLines(SDL_Renderer* renderer, SDL_Rect bounds, std::vector<SDL_Point> *points, SDL_Color fg , SDL_Colour bg);

#endif /* SPRITE_H_ */
