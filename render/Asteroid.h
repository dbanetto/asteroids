/*
 * Asteroid.h
 *
 *  Created on: Sep 15, 2013
 *      Author: drb
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "sprite.h"
#include <vector>

class Asteroid: public sprite {
public:
	Asteroid();
	virtual ~Asteroid();
	void generatePoints();
	void generateTexture(SDL_Renderer* renderer);

    virtual void render (double delta , SDL_Renderer* rednerer);
    virtual void update (double delta);

	double getAngle(void);
	void   setAngle(double angle);
protected:
	SDL_Point center;
	std::vector<SDL_Point> points;
	std::vector<SDL_Point> points_rotated;

	double angle;


private:
	SDL_Texture* texture;

	bool UPDATE_ROTATION;
	bool RENDER_TEXTURE;
};

#endif /* ASTEROID_H_ */
