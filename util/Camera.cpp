/*
 * Camera.cpp
 *
 *  Created on: 22/09/2013
 *      Author: drb
 */

#include "Camera.h"
#include "vector.h"

Camera::Camera()
{

}

Camera::Camera(SDL_Rect Viewport) {
	// TODO Auto-generated constructor stub
	this->viewport = Viewport;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

SDL_Point Camera::getCameraOffset()
{
	SDL_Point pt;
	pt.x = this->viewport.x;
	pt.y = this->viewport.y;
	return pt;
}
SDL_Rect  Camera::getViewPort()
{
	return this->viewport;
}

void Camera::BoxMoveWithSprite(sprite* sp) {
	SDL_Rect camera_movement_bounds;
	camera_movement_bounds.w = (this->viewport.w*0.9);
	camera_movement_bounds.h = (this->viewport.h*0.9);
	camera_movement_bounds.x = this->viewport.x + (this->viewport.w*0.05);
	camera_movement_bounds.y = this->viewport.y + (this->viewport.h*0.05);

	if ( !isWholeRectInside( sp->getBounds() , camera_movement_bounds ) ) {
		SDL_Rect product , sprite_bounds;
		sprite_bounds = sp->getBounds();
		SDL_IntersectRect( &sprite_bounds , &camera_movement_bounds , &product);
		//Time to find out which side of the square the rect is on
		//Check if the camera needs to move to the RIGHT
		if ((sprite_bounds.x + sprite_bounds.w) > (camera_movement_bounds.x + camera_movement_bounds.w) ) {
			this->viewport.x += (sprite_bounds.w) - (product.w);

		} else if (sprite_bounds.x < camera_movement_bounds.x ) {
			//Or check if it needs to move to the LEFT
			this->viewport.x += (sprite_bounds.x) - (product.x);

		}

		if ( (sprite_bounds.y + sprite_bounds.h) > (camera_movement_bounds.y + camera_movement_bounds.h) ) {
			this->viewport.y += (sprite_bounds.h) - (product.h);

		} else if ( sprite_bounds.y < camera_movement_bounds.y  ) {
			//Or check if it needs to move to the LEFT
			this->viewport.y += (sprite_bounds.y) - (product.y);
		}
	} else {

	}
	}
