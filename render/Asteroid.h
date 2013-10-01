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

class Asteroid: public sprite
{
public:
    Asteroid();
    virtual ~Asteroid();
    void generatePoints();
    void generateTexture(SDL_Renderer* renderer);

    void render (double delta , SDL_Renderer* rednerer , SDL_Point CameraOffset);
    void update (double delta);

protected:
    std::vector<SDL_Point> points;


private:
    SDL_Texture* texture;

    bool UPDATE_ROTATION;
    bool RENDER_TEXTURE;
};

#endif /* ASTEROID_H_ */
