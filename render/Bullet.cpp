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
	this->SPEED_MULTIPLIER = M_PI;
	SDL_Point pt;
	//Ship design

	point_bounds.reserve(5);
	pt.x = 0;
	pt.y = 0;
	point_bounds.push_back(pt);

	pt.x = 10;
	pt.y = 0;
	point_bounds.push_back(pt);

	pt.x = 10;
	pt.y = 4;
	point_bounds.push_back(pt);

	pt.x = 0;
	pt.y = 4;
	point_bounds.push_back(pt);

	pt.x = 0;
	pt.y = 0;
	point_bounds.push_back(pt);
	Point pt_ = Point();

	//For correct math
	this->setAngle(  Parent->getAngle() );

	auto parent_vel = Parent->getVelicoty();
	double vel_scalar = sqrt(parent_vel.x * parent_vel.x  + parent_vel.y * parent_vel.y) * this->SPEED_MULTIPLIER;

	pt_.x = cos((angle / 180.0) * M_PI ) * vel_scalar;
	pt_.y = sin((angle / 180.0) * M_PI) * vel_scalar;
	this->velicoty = pt_;

	auto p_pos = Parent->getPosition();
	this->position = p_pos;



	auto offset = SDL_Point(); offset.x = 2; offset.y = 5;
	this->center = offset;

	this->point_bounds = translate((this->point_bounds) , this->center , this->angle , this->position.toSDLPoint() );
	SDL_EnclosePoints( &(point_bounds[0]) , point_bounds.size() , NULL , &(this->bounds) );

	this->area = AreaOfPoints( this->point_bounds , this->center );
	this->setPosition(this->position);
}

Bullet::~Bullet()
{
	// TODO Auto-generated destructor stub
}

void Bullet::render (double delta , SDL_Renderer* renderer , SDL_Point CameraOffset)
{
	SDL_SetRenderDrawColor ( renderer , 255 , 255 , 255 , 255 );
	auto zero_pt = SDL_Point(); zero_pt.x = 0; zero_pt.y = 0;
	auto r = translate(this->point_bounds , this->center , 0 ,  PointSubtract( zero_pt , CameraOffset ));
	SDL_RenderDrawLines( renderer , &(r[0]) , this->point_bounds.size() );
}
void Bullet::update (double delta)
{
    this->position.x += (this->velicoty.x * delta);
    this->position.y += (this->velicoty.y * delta);
    this->setPosition(this->position);
	if (this->UPDATE_TRANSLATION)
	{
		//Sync Rect Bounds to position
		auto delta_pt = SDL_Point();
		delta_pt.x = round(this->velicoty.x * delta);
		delta_pt.y = round(this->velicoty.y * delta);

		this->point_bounds = translate(this->point_bounds , this->center , 0 , delta_pt );

		SDL_EnclosePoints( &(this->point_bounds[0]) , this->point_bounds.size() , NULL , &(this->bounds));
		this->UPDATE_TRANSLATION = false;
	}
}
void Bullet::event  (SDL_Event event, double delta)
{

}
