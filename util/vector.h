/*
 * Vector
 *
 *  Created on: 17/09/2013
 *      Author: drb
 */

#ifndef VECTOR_
#define VECTOR_

#include <vector>
#include "Point.h"
#include "../render/sprite.h"

std::vector<SDL_Point> translate (std::vector<SDL_Point> points, SDL_Point center , double angleDeg , SDL_Point Offset);
void translate (std::vector<SDL_Point>* points, SDL_Point center , double angleDeg , SDL_Point OffSet);


bool isPointInsidePolygon(SDL_Point pt , std::vector<SDL_Point>* polygon);
bool isPointInsidePolygon(SDL_Point pt , std::vector<SDL_Point> polygon);


bool isPolygonInsidePolygon(std::vector<SDL_Point>* pt , std::vector<SDL_Point>* polygon);
bool isPolygonInsidePolygon(std::vector<SDL_Point> pt , std::vector<SDL_Point> polygon);

bool isRectTouching (SDL_Rect* rect1, SDL_Rect* rect2);

bool isSpriteTouchingSprite (sprite sp1 , sprite sp2);

std::vector<SDL_Point> RectToPoints (SDL_Rect rect , double angle);




#endif /* VECTOR_ */
