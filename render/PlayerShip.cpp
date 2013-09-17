/*
 * PlayerShip.cpp
 *
 *  Created on: 10/09/2013
 *      Author: drb
 */

#include "PlayerShip.h"
#define _USE_MATH_DEFINES
#include <cmath>

PlayerShip::PlayerShip() : Ship(SHIP_CONTOLLER_PLAYER) {
    // TODO Auto-generated constructor stub
    this->TURN_RATE = 360;
    this->MOMENTUM_RATE = 25;
}

PlayerShip::~PlayerShip() {
    // Check if texture exists

}

void PlayerShip::update(double delta) {
	//Call base class update
	this->position.x += (this->momentum.x * delta);
	this->position.y += (this->momentum.y * delta);
	this->setPosition(this->position);
	this->Ship::update(delta);
}

void PlayerShip::input (const Uint8* state, double delta) {



    if (state[SDL_SCANCODE_A]) {
        this->angle -= (this->TURN_RATE * delta);
    }

    if (state[SDL_SCANCODE_D]) {
        this->angle += (this->TURN_RATE * delta);
    }

    if (state[SDL_SCANCODE_W]) {
        this->momentum.x += ( cos( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE * delta) );
        this->momentum.y += ( sin( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE * delta) );
    }

    if (state[SDL_SCANCODE_S]) {
        this->momentum.x -= ( cos( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE/2 * delta));
        this->momentum.y -= ( sin( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE/2 * delta));
    }

}
