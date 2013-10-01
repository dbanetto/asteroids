/*
 * PlayerShip.h
 *
 *  Created on: 10/09/2013
 *      Author: drb
 */

#ifndef PLAYERSHIP_H_
#define PLAYERSHIP_H_

#include "Ship.h"
#include <vector>
#include "Bullet.h"

class PlayerShip: public Ship
{
public:
    PlayerShip();
    virtual ~PlayerShip();
    void update (double delta);
    void render (double delta , SDL_Renderer* renderer , SDL_Point CameraOffset);
    void input (const Uint8* keys, double delta);
private:
    std::vector<Bullet> bullets;

};

#endif /* PLAYERSHIP_H_ */
