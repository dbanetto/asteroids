/*
 * sprite.cpp
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#include "sprite.h"
#define _USE_MATH_DEFINES
#include <cmath>


sprite::sprite() {
     // TODO Auto-generated constructor stub

}

sprite::~sprite() {
     // TODO Auto-generated destructor stub
}

void sprite::render (double delta , SDL_Renderer* rednerer)
{
     return;
}

void sprite::update (double delta)
{
     return;
}

void sprite::event (SDL_Event event, double delta) {
	return;
}

SDL_Rect sprite::getBounds(void) {
     return this->bounds;
}

void sprite::setBounds(SDL_Rect rect) {
     this->bounds = rect;
}

Point sprite::getPosition(void) {
     return this->position;
}
void sprite::setPosition(Point pt) {
	 this->position =pt;
	 this->bounds.x = round(pt.x);
     this->bounds.y = round(pt.y);
}

/*
 * Rotation using point rotation around the origin ( more here http://en.wikipedia.org/wiki/Rotation_%28mathematics%29 )
 * Angle in degrees
*/
std::vector<SDL_Point> rotate (std::vector<SDL_Point> points, SDL_Point center , double angle)
{
     //Create output vector
     std::vector<SDL_Point> n_points;
     //Reserve the same amount of points
     n_points.reserve(points.size());
     //Pre-calculate sin and cos as they will not change
     double a_sin = sin( (angle / 180.0) * M_PI );
     double a_cos = cos( (angle / 180.0) * M_PI );
     for (unsigned int i = 0; i < points.size(); i++) {
          SDL_Point pt;
          //Offset so the center is the origin of the points
          pt.x = points[i].x - center.x;
          pt.y = points[i].y - center.y;

          //Rotate the point around the origin by angle degrees

          int py = pt.y; int px = pt.x;
          pt.x = (px*a_cos - py*a_sin);
          pt.y = (px*a_sin + py*a_cos);

          //Returning the points back to before the origin change
          pt.x = pt.x + center.x;
          pt.y = pt.y + center.y;

          //Add them to the output list
          n_points.push_back(pt);
     }
     return n_points;
}

void rotate (std::vector<SDL_Point>* points, SDL_Point center , double angle)
{
     //Pre-calculate sin and cos as they will not change
     double a_sin = sin( (angle / 180.0) * M_PI );
     double a_cos = cos( (angle / 180.0) * M_PI );
     for (unsigned int i = 0; i < (*points).size(); i++) {
          SDL_Point pt;
          //Offset so the center is the origin of the points
          pt.x = (*points)[i].x - center.x;
          pt.y = (*points)[i].y - center.y;

          //Rotate the point around the origin by angle degrees
          int py = pt.y; int px = pt.x;
          pt.x = (px*a_cos - py*a_sin);
          pt.y = (px*a_sin + py*a_cos);

          //Returning the points back to before the origin change
          pt.x += center.x;
          pt.y += center.y;

          //Edit the points in the list
          (*points)[i].x = pt.x;
          (*points)[i].y = pt.y;
     }
}

/*
 * Tests if a given point is within a polygon
 * Using ray casting algorithm http://en.wikipedia.org/wiki/Point_in_polygon
*/
bool IsPointInsidePolygon (SDL_Point point , std::vector<SDL_Point>* polygon) {
     //Code converted from pseudo code from http://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
     //Credit for this snippet goes to http://stackoverflow.com/users/1830407/josh
     int i, j, nvert = (*polygon).size();
     bool c = false;

     for(i = 0, j = nvert - 1; i < nvert; j = i++) {
     if( ( (((*polygon)[i].y) >= point.y) != (((*polygon)[j].y >= point.y)) ) &&
          (point.x <= ((*polygon)[j].x - (*polygon)[i].x) * (point.y - (*polygon)[i].y) / ((*polygon)[j].y - (*polygon)[i].y) + (*polygon)[i].x)
       )
       c = !c;
     }

     return c;

}
