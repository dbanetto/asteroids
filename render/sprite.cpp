/*
 * sprite.cpp
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#include "sprite.h"

sprite::sprite() {
	// TODO Auto-generated constructor stub

}

sprite::~sprite() {
	// TODO Auto-generated destructor stub
}

void sprite::render (int delta , SDL_Renderer* rednerer)
{
	return;
}

void sprite::update (int delta)
{
	return;
}

SDL_Rect sprite::getBounds(void) {
	return this->bounds;
}

void sprite::setBounds(SDL_Rect rect) {
	this->bounds = rect;
}
