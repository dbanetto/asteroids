/*
 * Bullet.h
 *
 *  Created on: 1/10/2013
 *      Author: drb
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "sprite.h"
#include "Ship.h"

class Bullet : public sprite {
public:
	Bullet( Ship* Parent );
	virtual ~Bullet();
	void render (double delta , SDL_Renderer* renderer , SDL_Point CameraOffset);
	void update (double delta);
	void event  (SDL_Event event, double delta);
protected:
	Ship* parent;
	Point velicoty;
	int SPEED_MULTIPLIER;
};

#endif /* BULLET_H_ */
