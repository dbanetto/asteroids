/*
 * Ship.cpp
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#include "Ship.h"
#include <cmath>
#include <iostream>

Ship::Ship(SHIP_CONTROLLER controller) {
	// TODO Auto-generated constructor stub
	this->controller = controller;
	this->texture = nullptr;
	this->render_points = std::vector<SDL_Point>();

	this->boundary_points = std::vector<SDL_Point>();
	this->point_bounds = std::vector<SDL_Point>();
	this->RENDER_TEXTURE = true;
	this->UPDATE_TRANSLATION = false;

	//Add all the points to the point list
	render_points.reserve( 7 );
	SDL_Point pt;

	//Ship design
	pt.x = 1; pt.y = 0;
	render_points.push_back(pt);

	pt.x = 64; pt.y = 32;
	render_points.push_back(pt);

	pt.x = 1; pt.y = 64;
	render_points.push_back(pt);

	pt.x = 1; pt.y = 0;
	render_points.push_back(pt);

	pt.x = 21; pt.y = 32;
	render_points.push_back(pt);

	pt.x = 64; pt.y = 32;
	render_points.push_back(pt);

	pt.x = 21; pt.y = 32;
	render_points.push_back(pt);

	pt.x = 1; pt.y = 64;
	render_points.push_back(pt);

	//Boundary Points
	boundary_points.reserve(4);

	pt.x = 1; pt.y = 0;
	boundary_points.push_back(pt);

	pt.x = 64; pt.y = 32;
	boundary_points.push_back(pt);

	pt.x = 1; pt.y = 64;
	boundary_points.push_back(pt);

	pt.x = 32; pt.y = 32;
	boundary_points.push_back(pt);
	//Copy boundary points to boundary_rotated for initial values
	this->point_bounds = this->boundary_points;

	this->bounds = SDL_Rect();
	this->bounds.w = 64; this->bounds.h = 64; this->bounds.x = 0; this->bounds.y = 0;
	this->render_bounds = this->bounds;
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

void Ship::generateTexture(SDL_Renderer* renderer) {

	//Clean up any existing texture
	if (SDL_QueryTexture( this->texture , NULL , NULL , NULL , NULL) == 0) {
		//If the query is a  successes then the texture still exists
		SDL_DestroyTexture(this->texture);
	}
	SDL_Color fg; fg.r = 255; fg.g = 255; fg.b = 255; fg.a = 255;
	SDL_Color bg; bg.a = 0;
	this->texture = GenerateTextureLines(renderer , this->bounds , &(this->render_points), fg, bg );

	this->RENDER_TEXTURE = false;
}

void Ship::render (double delta , SDL_Renderer* renderer)
{
	//Check if the Texture needs a render update or to be pre-rendered
	if (this->RENDER_TEXTURE) {
		this->generateTexture(renderer);
	}
	this->setPosition(this->position);
   //Copy texture to the screen
   SDL_RenderCopyEx ( renderer , this->texture , NULL , &(this->bounds) , this->angle , &(this->center) ,SDL_FLIP_NONE );
}

void Ship::update (double delta)
{
	if (this->UPDATE_TRANSLATION) {
		this->setPosition(this->position);
		this->point_bounds = translate((this->boundary_points) , this->center , this->angle , this->position.toSDLPoint());
		this->UPDATE_TRANSLATION= false;
	}
}
