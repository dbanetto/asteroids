/*
 * PlayerShip.h
 *
 *  Created on: 10/09/2013
 *      Author: drb
 */

#ifndef PLAYERSHIP_H_
#define PLAYERSHIP_H_

#include "Ship.h"

class PlayerShip: public Ship {
public:
	PlayerShip();
	virtual ~PlayerShip();
	void update (double delta);

	void event (SDL_Event event, double delta);
private:
	Point momentum;
	double TURN_RATE;
	double MOMENTUM_RATE;
};

#endif /* PLAYERSHIP_H_ */
