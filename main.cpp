/*
 * main.cpp
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */


#include "GameWindow.h"
#include "util/env.h"

int main (int argc , char* args[]) {
	//Set background colour
	SDL_Color bg;
	bg.r = 0; bg.g = 0; bg.b = 0;

	GameWindow main = GameWindow();
	main.Init("Asteroids" , 800 , 600 , bg , SDL_WINDOW_OPENGL);
	main.Start();
	return 0;
}


