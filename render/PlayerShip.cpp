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
	this->TURN_RATE = 60;
	this->MOMENTUM_RATE = 50;
}

PlayerShip::~PlayerShip() {
	// Check if texture exists

}

void PlayerShip::update(double delta) {

	//Call base class update
	this->position.x += (this->momentum.x * delta);
	this->position.y += (this->momentum.y * delta);
	this->setPosition(this->position);

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_A]) {
		this->angle -= (this->TURN_RATE * delta);
		return;
	}
	if (state[SDL_SCANCODE_D]) {
		this->angle += (this->TURN_RATE * delta);
		return;
	}

	if (state[SDL_SCANCODE_W]) {
		this->momentum.x += ( cos( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE * delta) );
		this->momentum.y += ( sin( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE * delta) );
		return;
	}
	if (state[SDL_SCANCODE_S]) {
		this->momentum.x -= ( cos( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE * delta));
		this->momentum.y -= ( sin( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE * delta));
		return;
	}

	this->Ship::update(delta);
}

void PlayerShip::event (SDL_Event e, double delta) {
		if (e.key.keysym.sym == SDLK_a && e.key.state == SDL_PRESSED) {
			this->angle -= (this->TURN_RATE * delta);
			return;
		}
		if (e.key.keysym.sym == SDLK_d && e.key.state == SDL_PRESSED) {
			this->angle += (this->TURN_RATE * delta);
			return;
		}

		if (e.key.keysym.sym == SDLK_w && e.key.state == SDL_PRESSED) {
			this->momentum.x += ( cos( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE * delta) );
			this->momentum.y += ( sin( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE * delta) );
			return;
		}
		if (e.key.keysym.sym == SDLK_s && e.key.state == SDL_PRESSED) {
			this->momentum.x -= ( cos( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE * delta));
			this->momentum.y -= ( sin( (this->angle / 180.0) * M_PI ) * ceil(this->MOMENTUM_RATE * delta));
			return;
		}

}
