/*
 * PlayerShip.cpp
 *
 *  Created on: 10/09/2013
 *      Author: drb
 */

#include "PlayerShip.h"
#define _USE_MATH_DEFINES
#include <cmath>

PlayerShip::PlayerShip() : Ship(SHIP_CONTOLLER_PLAYER)
{
    // TODO Auto-generated constructor stub
    this->TURN_RATE = 360;
    this->VELICOTY_RATE = 25;
}

PlayerShip::~PlayerShip()
{
    // Check if texture exists
	this->bullets.clear();

}

void PlayerShip::render(double delta , SDL_Renderer* renderer , SDL_Point CameraOffset)
{
    for (unsigned int i = 0; i < this->bullets.size(); i++) {
    	this->bullets[i].render(delta , renderer, CameraOffset);
    }
    Ship::render( delta , renderer , CameraOffset);
}

void PlayerShip::update(double delta)
{
    //Call base class update
    this->position.x += (this->velicoty.x * delta);
    this->position.y += (this->velicoty.y * delta);
    this->setPosition(this->position);
    for (unsigned int i = 0; i < this->bullets.size(); i++) {
    	auto bullet_pos = this->bullets[i].getPosition();
    	if (position.Distance( &(bullet_pos) , &(this->position) ) > 1000 )
    	{
    		this->bullets.erase( this->bullets.begin() + i );
    	} else {
    		this->bullets[i].update(delta);
    	}
    }
    this->Ship::update(delta);
}

void PlayerShip::input (const Uint8* state, double delta)
{
	if (state[SDL_SCANCODE_G]) {
		Bullet bt =  Bullet(this);
		this->bullets.push_back(bt);
	}
    if (state[SDL_SCANCODE_A])
    {
        this->angle -= (this->TURN_RATE * delta);
    }

    if (state[SDL_SCANCODE_D])
    {
        this->angle += (this->TURN_RATE * delta);
    }

    if (state[SDL_SCANCODE_W])
    {
        this->velicoty.x += ( cos( (this->angle / 180.0) * M_PI ) * ceil(this->VELICOTY_RATE * delta) );
        this->velicoty.y += ( sin( (this->angle / 180.0) * M_PI ) * ceil(this->VELICOTY_RATE * delta) );
    }

    if (state[SDL_SCANCODE_S])
    {
        this->velicoty.x -= ( cos( (this->angle / 180.0) * M_PI ) * ceil(this->VELICOTY_RATE/2 * delta));
        this->velicoty.y -= ( sin( (this->angle / 180.0) * M_PI ) * ceil(this->VELICOTY_RATE/2 * delta));
    }

}
