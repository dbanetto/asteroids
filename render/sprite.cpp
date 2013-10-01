/*
 * sprite.cpp
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#include "sprite.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

sprite::sprite()
{
    // TODO Auto-generated constructor stub
    this->UPDATE_TRANSLATION = true;
    this->angle = 0;
}

sprite::~sprite()
{
    // TODO Auto-generated destructor stub
    this->point_bounds.clear();
}

void sprite::render (double delta , SDL_Renderer* rednerer, SDL_Point CameraOffset)
{
    return;
}

void sprite::update (double delta)
{
    return;
}

void sprite::event (SDL_Event event, double delta)
{
    return;
}

SDL_Rect sprite::getBounds(void)
{
    return this->bounds;
}

SDL_Point* sprite::getPointBoundsArray()
{
    return &(this->point_bounds[0]);
}

std::vector<SDL_Point>* sprite::getPointBounds ()
{
    return &(this->point_bounds);
}

void sprite::setBounds(SDL_Rect rect)
{
    this->bounds = rect;
    UPDATE_TRANSLATION = true;
}

Point sprite::getPosition(void)
{
    return this->position;
}
void sprite::setPosition(Point pt)
{
    this->position = pt;
    this->bounds.x = round(pt.x);
    this->bounds.y = round(pt.y);
    this->render_bounds.x = round(pt.x);
    this->render_bounds.y = round(pt.y);
    UPDATE_TRANSLATION = true;
}

SDL_Point sprite::getCenter ()
{
    return this->center;
}

double sprite::getAngle(void)
{
    return this->angle;
}

void   sprite::setAngle(double a)
{
    //Keep the angle between (-360,360)
    this->angle = fmod(a,360);
    //Set flag to update the collision points next update
    this->UPDATE_TRANSLATION = true;
}

double sprite::getArea ()
{
    return this->area;
}
