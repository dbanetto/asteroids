/*
 * Ship.cpp
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#include "Ship.h"

Ship::Ship(SHIP_CONTROLLER controller) {
	// TODO Auto-generated constructor stub
	this->controller = controller;
	this->texture = nullptr;
	this->points = std::vector<SDL_Point>();
	//Ship design
	//Add all the points to the point list
	points.reserve( 7 );
	SDL_Point pt;
	pt.x = 32; pt.y = 0;
	points.push_back(pt);

	pt.x = 64; pt.y = 63;
	points.push_back(pt);

	pt.x = 0; pt.y = 63;
	points.push_back(pt);

	pt.x = 32; pt.y = 0;
	points.push_back(pt);

	pt.x = 32; pt.y = 42;
	points.push_back(pt);

	pt.x = 0; pt.y = 63;
	points.push_back(pt);

	pt.x = 32; pt.y = 42;
	points.push_back(pt);

	pt.x = 64; pt.y = 63;
	points.push_back(pt);

	this->bounds = SDL_Rect();
	this->bounds.w = 64; this->bounds.h = 64; this->bounds.x = 0; this->bounds.y = 0;
	this->center.x = 32; this->center.y = 32;
	this->angle = 0;
}

Ship::~Ship() {
	// Check if texture exists
	if (SDL_QueryTexture( this->texture , NULL , NULL , NULL , NULL) == 0) {
		//If the query is a  successes then the texture still exists
		SDL_DestroyTexture(this->texture);
	}
}

int Ship::generateTexture(SDL_Renderer* renderer) {
	//Clean up any existing texture
	if (SDL_QueryTexture( this->texture , NULL , NULL , NULL , NULL) == 0) {
			//If the query is a  successes then the texture still exists
			SDL_DestroyTexture(this->texture);
		}

	//Check if the Ship can be pre-rendered and saved as texture
   if ( SDL_RenderTargetSupported(renderer) ) {
		//Create backup of current render target
		SDL_Texture* bck = SDL_GetRenderTarget ( renderer );
		//Create new texture for the circle to call home*
		SDL_Texture* ship = SDL_CreateTexture (renderer ,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,this->bounds.w, this->bounds.h);
		//Change the render target to the Circle target
		SDL_SetRenderTarget ( renderer, ship );

		//TODO : Make rendered targets have transparency
		//WHY DOES IT NOT MAKE TRANSPARNT
		SDL_SetRenderDrawColor ( renderer , 05 , 05 , 05 , 0);
		//Clean the texture, I think
		SDL_RenderClear ( renderer );

		//Set Ship Colour
		SDL_SetRenderDrawColor ( renderer , 250 , 250 , 250 , 255);
		//Render to texture
		SDL_RenderDrawLines(renderer , &(this->points[0]) , this->points.size());
		//Update texture
		this->texture = ship;
		//Restore render target
		SDL_SetRenderTarget ( renderer, bck );
		return 0;
   } else {
	//Targeted rendering not supported
	   return -1;
   }
}

void Ship::render (int delta , SDL_Renderer* renderer)
{
   //Copy texture to the screen
   SDL_RenderCopyEx ( renderer , this->texture , NULL , &(this->bounds) , this->angle , &(this->center) ,SDL_FLIP_NONE );
}

void Ship::update (int delta)
{

}

double Ship::getAngle(void) {
	return this->angle;
}
void   Ship::setAngle(double a){
	this->angle = a;
}
