/*
 * Camera.h
 *
 *  Created on: 22/09/2013
 *      Author: drb
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "SDL2/SDL.h"
#include "../render/sprite.h"

class Camera {
public:
	Camera();
	Camera(SDL_Rect view_port);
	void chase (sprite* sp);

	SDL_Point getCameraOffset();
	SDL_Rect  getViewPort();

	void BoxMoveWithSprite (sprite* sp);

	virtual ~Camera();
private:
	SDL_Rect viewport;
};

#endif /* CAMERA_H_ */
