/*
 * area.cpp
 *
 *  Created on: 23/09/2013
 *      Author: drb
 */

#include "area.h"
#include "vector.h"
#include <iostream>
#include <vector>
#include <limits>
#include "math.h"
#include <algorithm>
bool double_gtr_sort (double a, double b) { return (a>b); }

double AreaOfPoints ( std::vector<SDL_Point> points , SDL_Point center ) {
	double area = 0;
	//Calculate the area of the polygon from making points from the center
	//Then making triangle from 2 points to the center
	//The Base of the triangle is the distance between point 1 and 2
	//The height of the triangle is distance from the midpoint of points 1 and 2, to the center.
	for (unsigned int i = 0; i < points.size(); i ++) {

		unsigned in = (i == 0 ? points.size() -1 : i -1 );
		std::vector<double> lengths;
		lengths.reserve(3);
		lengths.resize(3);
		// http://en.wikipedia.org/wiki/Heron%27s_formula
		lengths[0] = ( distance(points[i] , points[in] ));
		lengths[1] = ( distance(center , points[i] ) );
		lengths[2] = ( distance(center , points[in] ) );
		//Sort list
		std::sort (lengths.begin() , lengths.end() , double_gtr_sort );

		// http://upload.wikimedia.org/math/1/7/c/17c41c9c2a57227d91fb7921c6ef78f4.png
		area += 0.25 * SDL_sqrt(
				(lengths[0] + (lengths[1] + lengths[2])) *
				(lengths[2] - (lengths[0] - lengths[1])) *
				(lengths[2] + (lengths[0] - lengths[1])) *
				(lengths[0] + (lengths[1] - lengths[2]))
				);
	}
	return area;
}

double AreaOfRect (SDL_Rect rect) {
	return rect.w * rect.h;
}
