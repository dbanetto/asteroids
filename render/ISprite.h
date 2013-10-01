/*
 * ISprite.h
 *
 *  Created on: 28/09/2013
 *      Author: drb
 */

#ifndef ISPRITE_H_
#define ISPRITE_H_

#include <vector>
#include "../util/Point.h"

class ISprite
{

public:
    ISprite();
    virtual ~ISprite();
    virtual void render (double delta , SDL_Renderer* rednerer , SDL_Point CameraOffset) = 0;
    virtual void update (double delta) = 0;
    virtual void event  (SDL_Event event, double delta) = 0;
    virtual SDL_Rect getBounds(void) = 0;
    virtual void setBounds(SDL_Rect rect) = 0;

    virtual double getAngle(void) = 0;
    virtual void   setAngle(double angle) = 0;

    virtual Point getPosition(void) = 0;
    virtual void setPosition(Point pos) = 0;
    virtual SDL_Point getCenter () = 0;
    virtual std::vector<SDL_Point>* getPointBounds () = 0;
    virtual SDL_Point* getPointBoundsArray () = 0;


    virtual double getArea() = 0;
protected:
    SDL_Rect  bounds;
    SDL_Rect  render_bounds;
    Point     position;
    SDL_Point center;
    std::vector<SDL_Point> point_bounds;
    bool UPDATE_TRANSLATION;
    double area;
    double angle;
};

#endif /* ISPRITE_H_ */
