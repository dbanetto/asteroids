/*
 * main.cpp
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */


#include "GameWindow.h"
#include <iostream>
int main (int argc , char* args[]) {
     //Set background colour
     SDL_Color bg;  bg.r = 0; bg.g = 0; bg.b = 0;

     GameWindow main = GameWindow();
     main.Init("Asteroids" , 1280 , 720 , bg , SDL_WINDOW_OPENGL);
     try {
     main.Start();
     } catch (int ex) {
    	 std::cout << ex << std::endl;
     }
     return 0;
}
