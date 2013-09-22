/*
 * Asteroid.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: drb
 */

#include "Asteroid.h"
#include <cstdlib>
#include <time.h>
#include <cmath>

#include "render.h"
#include "../util/vector.h"

Asteroid::Asteroid() : sprite() {
	// TODO Auto-generated constructor stub
	this->texture = nullptr;
	this->points.clear();
	this->point_bounds.clear();
	this->UPDATE_ROTATION = true;
	this->RENDER_TEXTURE = true;
	this->bounds.w = 64; this->bounds.h = 64;
	this->position.x = 64; this->position.y = 64;
	this->render_bounds = this->bounds;
	this->angle = 0.0;
	generatePoints();
}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}

void Asteroid::generatePoints() {
	//Generate Circle with the range from 0 to 2pi
	int points = rand() % 5 + 5;
	float steps = M_PI / points;
	this->points.clear();
	this->points = std::vector<SDL_Point>();
	this->points.reserve(points + 1);

	SDL_Point center;
	center.x = 32;
	center.y = 32;
	//Start random number gen
	//srand( time(NULL) );

	for (float angle = 0; angle < 2 * M_PI; angle += steps) {

	   double radius = (rand() % 16) + 15;

	   SDL_Point pt;
	   pt.x = (int)(cosf( angle ) * radius) + center.x;
	   pt.y = (int)(sinf( angle ) * radius) + center.y;
	   if (pt.x < 0 && pt.y < 0) {
		   continue;
		}

	   if (this->points.size() > 1) {
		   if (this->points[this->points.size()-1].x == pt.x && this->points[this->points.size()-1].y == pt.y) {
			   //Point is the same as the last point, there is NO REASON to add it
			   continue;
		   } else {
			   this->points.push_back(pt);
			   continue;
		   }
	   } else {
		   this->points.push_back(pt);
		   continue;
	   }
	}

	this->point_bounds = this->points;
	this->points.push_back(this->points[0]);
	this->RENDER_TEXTURE = true;
	this->UPDATE_ROTATION = true;

	SDL_EnclosePoints( &(this->point_bounds[0]) , this->point_bounds.size() , NULL , &(this->bounds));
	this->center.x = this->bounds.w/2;
	this->center.y = this->bounds.h/2;
}

void Asteroid::generateTexture(SDL_Renderer* renderer) {
	 //Clean up any existing texture
     if (SDL_QueryTexture( this->texture , NULL , NULL , NULL , NULL) == 0) {
               //If the query is a  successes then the texture still exists
               SDL_DestroyTexture(this->texture);
     }
     SDL_Color fg; fg.r = 255; fg.g = 255; fg.b = 255; fg.a = 255;
     SDL_Color bg; bg.a = 0;
     this->texture = GenerateTextureLines(renderer , this->render_bounds , &(this->points), fg, bg  );
     this->RENDER_TEXTURE = false;
}

void Asteroid::render (double delta , SDL_Renderer* renderer , SDL_Point CameraOffset)
{
	/*
}
	//Check if the Texture needs a render update or to be pre-rendered
	if (this->RENDER_TEXTURE) {
		this->generateTexture(renderer);
	}

	//Copy texture to the screen
	SDL_RenderCopyEx ( renderer , this->texture , NULL , &(this->bounds) , this->angle , &(this->center) , SDL_FLIP_NONE );*/

	SDL_SetRenderDrawColor ( renderer , 255 , 255 , 255 , 255 );
   	std::vector<SDL_Point> tr = translate ( point_bounds , this->center , 0 , PointSubtract( SDL_Point() , CameraOffset) ) ;
	SDL_RenderDrawLines( renderer , &(tr[0]) , this->points.size() );

}

void Asteroid::update (double delta)
{
	this->angle += 6 * delta ;
	this->UPDATE_TRANSLATION = true;
     if (this->UPDATE_TRANSLATION) {

    	 this->point_bounds = translate((this->points) , this->center , this->angle , this->position.toSDLPoint() );
    	 SDL_EnclosePoints( &(this->point_bounds[0]) , this->point_bounds.size() , NULL , &(this->bounds));
		 //Sync Rect Bounds to position
		 this->setPosition(this->position);
    	 this->UPDATE_TRANSLATION = false;
     }
}
