/*
 * AreaMap.h
 *
 *  Created on: 20/09/2013
 *      Author: drb
 */

#ifndef AREAMAP_H_
#define AREAMAP_H_

#include "../render/sprite.h"
#include <vector>

class AreaMap {
public:
	AreaMap();
	AreaMap(AreaMap* Parent , SDL_Rect Area);
	virtual ~AreaMap();

	void insert(sprite* sp);
	std::vector<sprite*> getSpritesFromArea (SDL_Rect Area);

	SDL_Rect getArea();

	void clear();
protected:
	SDL_Rect area;
	std::vector<sprite*>  sprites;
	std::vector<AreaMap> children;
	AreaMap* parent;
private:
	void split();
};

#endif /* AREAMAP_H_ */
