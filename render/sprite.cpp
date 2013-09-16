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
#include "../util/env.h"

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

std::vector<SDL_Point>* sprite::getPointBounds ()
{
	return &(this->point_bounds);
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

SDL_Point sprite::getCenter () {
	return this->center;
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
bool IsPointInsidePolygon (SDL_Point point , std::vector<SDL_Point>* points) {
     //Code converted from pseudo code from http://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
     //Credit for this snippet goes to http://stackoverflow.com/users/1830407/josh
	int i, j, nvert = points->size();
	  bool c = false;

	  for(i = 0, j = nvert - 1; i < nvert; j = i++) {
	    if(  ( ( (*points)[i].y ) >= point.y) != ( ((*points)[j].y >= point.y) ) &&
	        (point.x <= ((*points)[j].x - (*points)[i].x) * (point.y - (*points)[i].y) / ((*points)[j].y - (*points)[i].y) + (*points)[i].x))

	      c = !c;
	  }

	  return c;

}

bool isPolygonInsidePolygon(std::vector<SDL_Point>* pt , std::vector<SDL_Point>* polygon)
{
	//Cycle through all the points of one polygon
	for (unsigned int i = 0; i < (*pt).size(); i++) {
		if ( IsPointInsidePolygon( (*pt)[i] , polygon) ) {
			return true;
		}
	}
	return false;
}

bool isRectTouching (SDL_Rect aRect, SDL_Rect bRect)
{
	/*
	* Point's for rectangle (x,y) , (x+w,y) , (x+w,y+h) , (x,y+h)
	* Checks if the points are in the bounds of each other
	* Pointers to SDL_rect's are used for faster(?) usage of properties
	*/
	    if (aRect.x < (bRect.x + bRect.w) && (aRect.x + aRect.w) > bRect.x &&
	        aRect.y < (bRect.y + bRect.h) && (aRect.y + aRect.h) > bRect.y)
	    {
	        return true;
	    } else {
	        return false;
	    }
}

bool isSpriteTouchingSprite (sprite sp1 , sprite sp2)
{
	if ( isRectTouching( sp1.getBounds() , sp2.getBounds() ) ) {
		bool touching = isPolygonInsidePolygon( sp1.getPointBounds() , sp2.getPointBounds() );
		return touching;
	}
	return false;
}

SDL_Texture* GenerateTextureLines(SDL_Renderer* renderer, SDL_Rect bounds, std::vector<SDL_Point> *points, SDL_Color fg , SDL_Colour bg) {
    //Check if the Ship can be pre-rendered and saved as texture
	 SDL_Surface* surface = SDL_CreateRGBSurface(0, bounds.w, bounds.h, 32,
								   rmask, gmask, bmask, amask);

	 //Create a software Render with target of surface
	 SDL_Renderer* swRender = SDL_CreateSoftwareRenderer(surface);

	 //Set Render colour before cleaning
	 SDL_SetRenderDrawColor ( swRender , bg.r , bg.g , bg.b , bg.a);

	 //Clean the render target
	 SDL_RenderClear ( swRender );

	 //Set Ship Colour
	 SDL_SetRenderDrawColor ( swRender , fg.r , fg.g , fg.b , fg.a);

	 //Render to the Render target
	 SDL_RenderDrawLines(swRender , &( (*points)[0]) , (*points).size());

	 //Convert the surface to a texture, needs main renderer
	 SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer , surface);

	 //Delete render
	 SDL_DestroyRenderer(swRender);

	 //Free surface
	 SDL_FreeSurface(surface);

	 return texture;
}
