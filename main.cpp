/*
 * main.cpp
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */


#include "GameWindow.h"
#include <iostream>

#include "io/Settings.h"

int main (int argc , char* args[]) {
	//Set background colour
	SDL_Color bg;  bg.r = 0; bg.g = 0; bg.b = 0;

	Settings set;

	if (!set.open(SETTINGS_LOCATION)) {
		std::cout << "Settings ( settings.ini ) file did not load" << std::endl;
		return -1;
	}
	set.load(0);

	GameWindow main = GameWindow();
	main.Init("Asteroids"
		,  set.getInt("screen.width")
		,  set.getInt("screen.height")
		, bg
		, SDL_WINDOW_OPENGL);

	set.close();
	set.clear();

	try {
		main.Start();
	} catch (int ex) {
		std::cout << ex << std::endl;
	}

     return 0;
}
