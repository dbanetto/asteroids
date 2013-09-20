/*
 * sprite.h
 *
 *  Created on: Sep 8, 2013
 *      Author: drb
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <vector>
#include "../util/Point.h"

class sprite {
public:
     sprite();
     virtual ~sprite();
     virtual void render (double delta , SDL_Renderer* rednerer , SDL_Point CameraOffset);
     virtual void update (double delta);
     virtual void event  (SDL_Event event, double delta);
     SDL_Rect getBounds(void);
     void setBounds(SDL_Rect rect);

     double getAngle(void);
     void   setAngle(double angle);

     Point getPosition(void);
     void setPosition(Point pos);
     SDL_Point getCenter ();
     std::vector<SDL_Point>* getPointBounds ();
     SDL_Point* getPointBoundsArray ();

protected:
     SDL_Rect  bounds;
     SDL_Rect  render_bounds;
     Point     position;
     SDL_Point center;
     std::vector<SDL_Point> point_bounds;
     bool UPDATE_TRANSLATION;

     double angle;
};

#endif /* SPRITE_H_ */
