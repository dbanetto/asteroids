/*
 * Point.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: drb
 */

#include "Point.h"
#include <cmath>

Point::Point()
{
    // TODO Auto-generated constructor stub
    this->x = 0;
    this->y = 0;
}

Point::~Point()
{
    // TODO Auto-generated destructor stub
}

Point::Point(double X, double Y)
{
    this->x = Y;
    this->y = X;
}

double Distance (Point* p1 , Point* p2)
{
    return sqrt( pow(p1->x - p2->x, 2) + pow(p1->y - p2->y , 2) );
}

void Point::operator= (const Point& p)
{
    this->x = p.x;
    this->y = p.y;
}
void Point::operator+ (const Point& p)
{
    this->x += p.x;
    this->y += p.y;
}
void Point::operator- (const Point& p)
{
    this->x -= p.x;
    this->y -= p.y;
}

void Point::operator* (const int& p) {
	this->x *= p;
	this->y *= p;
}

SDL_Point Point::toSDLPoint()
{
    SDL_Point p;
    p.x = round(this->x);
    p.y = round(this->y);
    return p;
}
