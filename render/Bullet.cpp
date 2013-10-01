/*
 * Bullet.cpp
 *
 *  Created on: 1/10/2013
 *      Author: drb
 */

#include "Bullet.h"
#include "../util/vector.h"
#include "../util/area.h"
#include "../util/vector.h"

Bullet::Bullet ( Ship* Parent )
{
	this->parent = Parent;
	this->SPEED_MULTIPLIER = 1;
	SDL_Point pt;
	//Ship design

	point_bounds.reserve(5);
	pt.x = 0;
	pt.y = 0;
	point_bounds.push_back(pt);

	pt.x = 0;
	pt.y = 10;
	point_bounds.push_back(pt);

	pt.x = 4;
	pt.y = 10;
	point_bounds.push_back(pt);

	pt.x = 4;
	pt.y = 0;
	point_bounds.push_back(pt);

	pt.x = 0;
	pt.y = 0;
	point_bounds.push_back(pt);
	Point pt_ = Point();
	//pt_.x = Parent->getVelicoty().x * this->SPEED_MULTIPLIER;
	//pt_.y = Parent->getVelicoty().y * this->SPEED_MULTIPLIER;
	this->velicoty = pt_;
	this->position = Parent->getPosition();
	this->angle = Parent->getAngle();
	this->setPosition(this->position);

	SDL_EnclosePoints( &(point_bounds[0]) , point_bounds.size() , NULL , &(this->bounds) );
	this->area = AreaOfPoints( this->point_bounds , this->center );
}

Bullet::~Bullet()
{
	// TODO Auto-generated destructor stub
}

void Bullet::render (double delta , SDL_Renderer* renderer , SDL_Point CameraOffset)
{
	SDL_SetRenderDrawColor ( renderer , 255 , 255 , 255 , 255 );
	std::vector<SDL_Point> r = translate(this->point_bounds , this->center , this->angle ,  PointSubtract(this->position.toSDLPoint() , CameraOffset ));
	SDL_RenderDrawLines( renderer , &(r[0]) , this->point_bounds.size() );
}
void Bullet::update (double delta)
{
    this->position.x += (this->velicoty.x * delta);
    this->position.y += (this->velicoty.y * delta);
    this->setPosition(this->position);
	if (this->UPDATE_TRANSLATION)
	    {
	        this->point_bounds = translate((this->point_bounds) , this->center , this->angle , this->position.toSDLPoint());
	        SDL_EnclosePoints( &(this->point_bounds[0]) , this->point_bounds.size() , NULL , &(this->bounds));
	        //Sync Rect Bounds to position
	        this->setPosition(this->position);
	        this->UPDATE_TRANSLATION = false;
	    }
}
void Bullet::event  (SDL_Event event, double delta)
{

}
