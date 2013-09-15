/*
 * Ship.cpp
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#include "Ship.h"
#include <cmath>
#include "../util/env.h"
#include <iostream>

Ship::Ship(SHIP_CONTROLLER controller) {
     // TODO Auto-generated constructor stub
     this->controller = controller;
     this->texture = nullptr;
     this->render_points =                std::vector<SDL_Point>();

     this->boundary_points =          std::vector<SDL_Point>();
     this->boundary_points_rotated = std::vector<SDL_Point>();
     this->RENDER_TEXTURE = true;
     this->UPDATE_ROTATION = false;

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
     boundary_points.reserve(3);

     pt.x = 1; pt.y = 0;
     boundary_points.push_back(pt);

     pt.x = 64; pt.y = 32;
     boundary_points.push_back(pt);

     pt.x = 1; pt.y = 64;
     boundary_points.push_back(pt);
     //Copy boundary points to boundary_rotated for initial values
     this->boundary_points_rotated = this->boundary_points;

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
	 SDL_Surface* surface = SDL_CreateRGBSurface(0, this->bounds.w, this->bounds.h, 32,
								   rmask, gmask, bmask, amask);

	 //Create a software Render with target of surface
	 SDL_Renderer* swRender = SDL_CreateSoftwareRenderer(surface);

	 //Set Render colour before cleaning
	 SDL_SetRenderDrawColor ( swRender , 0 , 0 , 0 , 0);

	 //Clean the render target
	 SDL_RenderClear ( swRender );

	 //Set Ship Colour
	 SDL_SetRenderDrawColor ( swRender , 250 , 250 , 250 , 255);

	 //Render to the Render target
	 SDL_RenderDrawLines(swRender , &(this->render_points[0]) , this->render_points.size());

	 //Convert the surface to a texture, needs main renderer
	 SDL_Texture* ship = SDL_CreateTextureFromSurface(renderer , surface);

	 //Update texture
	 this->texture = ship;

	 //Delete render
	 SDL_DestroyRenderer(swRender);

	 //Free surface
	 SDL_FreeSurface(surface);

	 this->RENDER_TEXTURE = false;

	 return 0;
}

void Ship::render (double delta , SDL_Renderer* renderer)
{
	//Check if the Texture needs a render update or to be pre-rendered
     if (this->RENDER_TEXTURE) {
          this->generateTexture(renderer);
     }

   //Copy texture to the screen
   SDL_RenderCopyEx ( renderer , this->texture , NULL , &(this->bounds) , this->angle , &(this->center) ,SDL_FLIP_NONE );
}

void Ship::update (double delta)
{
     if (this->UPDATE_ROTATION) {
          this->boundary_points_rotated = rotate((this->boundary_points) , this->center , this->angle);
          this->UPDATE_ROTATION= false;
     }
}

double Ship::getAngle(void) {
     return this->angle;
}

void   Ship::setAngle(double a){
     //Keep the angle between (-360,360)
	 this->angle = fmod(a,360);
     //Set flag to update the collision points next update
	 this->UPDATE_ROTATION = true;
}
