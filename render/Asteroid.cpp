/*
 * Asteroid.cpp
 *
 *  Created on: Sep 15, 2013
 *      Author: drb
 */

#include "Asteroid.h"
#include <cstdlib>
#include <time.h>

Asteroid::Asteroid() : sprite() {
	// TODO Auto-generated constructor stub
	this->texture = nullptr;
	this->points.clear();
	this->points_rotated.clear();
	this->UPDATE_ROTATION = true;
	this->RENDER_TEXTURE = true;
	this->bounds.w = 64;
	this->bounds.h = 64;

	generatePoints();
}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}

void Asteroid::generatePoints() {
	//Generate Circle with the range from 0 to 2pi
	float steps = M_PI / 5;
	this->points.clear();
	this->points = std::vector<SDL_Point>();
	this->points.reserve(6);

	SDL_Point center;
	center.x = 32;
	center.y = 32;
	//Start random number gen
	srand( time(NULL) );

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
	this->points.push_back(this->points[0]);
}

void Asteroid::generateTexture(SDL_Renderer* renderer) {
	//Clean up any existing texture

     if (SDL_QueryTexture( this->texture , NULL , NULL , NULL , NULL) == 0) {
               //If the query is a  successes then the texture still exists
               SDL_DestroyTexture(this->texture);
     }

     this->texture = GenerateTextureLines(renderer , this->bounds , &(this->points) );

}

void Asteroid::render (double delta , SDL_Renderer* renderer)
{
	//Check if the Texture needs a render update or to be pre-rendered
     if (this->RENDER_TEXTURE) {
          this->generateTexture(renderer);
     }

   //Copy texture to the screen
   SDL_RenderCopyEx ( renderer , this->texture , NULL , &(this->bounds) , this->angle , &(this->center) ,SDL_FLIP_NONE );
}

void Asteroid::update (double delta)
{
     if (this->UPDATE_ROTATION) {
          this->points_rotated = rotate((this->points) , this->center , this->angle);
          this->UPDATE_ROTATION= false;
     }
}

double Asteroid::getAngle(void) {
     return this->angle;
}

void Asteroid::setAngle(double a){
     //Keep the angle between (-360,360)
	 this->angle = fmod(a,360);
     //Set flag to update the collision points next update
	 this->UPDATE_ROTATION = true;
}
