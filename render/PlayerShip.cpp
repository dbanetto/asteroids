/*
 * PlayerShip.cpp
 *
 *  Created on: 10/09/2013
 *      Author: drb
 */

#include "PlayerShip.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cfloat>

PlayerShip::PlayerShip() : Ship(SHIP_CONTOLLER_PLAYER) {
	// TODO Auto-generated constructor stub
	momentum_x = 0;
	momentum_y = 0;
}

PlayerShip::~PlayerShip() {
	// Check if texture exists

}

void PlayerShip::update(double delta) {

	//Call base class update
	this->bounds.x += (this->momentum_x * delta);
	this->bounds.y += (this->momentum_y * delta);
	this->Ship::update(delta);
}

void PlayerShip::event (SDL_Event e, double delta) {
	if (e.key.keysym.sym == SDLK_a) {
		this->angle -= (100 * delta);
		return;
	}
	if (e.key.keysym.sym == SDLK_d) {
		this->angle += (100 * delta);
		return;
	}

	if (e.key.keysym.sym == SDLK_w) {
		this->momentum_x += ( cos( (this->angle / 180.0) * M_PI ) * ceil(50 * delta) );
		this->momentum_y += ( sin( (this->angle / 180.0) * M_PI ) * ceil(50 * delta) );
		return;
	}
	if (e.key.keysym.sym == SDLK_s) {
		this->momentum_x -= ( cos( (this->angle / 180.0) * M_PI ) * ceil(50 * delta));
		this->momentum_y -= ( sin( (this->angle / 180.0) * M_PI ) * ceil(50 * delta));
		return;
	}
}
