/*
 * sprite.h
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDL2/SDL.h"

class sprite {
public:
	sprite();
	virtual ~sprite();
	virtual void render (int delta , SDL_Renderer* rednerer);
	virtual void update (int delta);

	SDL_Rect getBounds(void);
	void setBounds(SDL_Rect rect);
protected:
	SDL_Rect bounds;
};

#endif /* SPRITE_H_ */
