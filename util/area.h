/*
 * area.h
 *
 *  Created on: 23/09/2013
 *      Author: drb
 */

#ifndef AREA_H_
#define AREA_H_

#include "SDL2/SDL.h"
#include <vector>

double AreaOfPoints ( std::vector<SDL_Point> points , SDL_Point center );
double AreaOfRect   (SDL_Rect rect);

#endif /* AREA_H_ */
