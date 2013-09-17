/*
 * Point.h
 *
 *  Created on: Sep 15, 2013
 *      Author: drb
 */

#ifndef POINT_H_
#define POINT_H_

#include "SDL2/SDL.h"

class Point {
public:
	Point();
	Point(double x, double y);
	virtual ~Point();
	double x , y;

	SDL_Point toSDLPoint();

	Point operator= (const Point& p);
	Point operator+ (const Point& p);
	Point operator- (const Point& p);
};

double Distance (Point* p1 , Point* p2);

#endif /* POINT_H_ */
