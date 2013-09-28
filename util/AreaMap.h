/*
 * AreaMap.h
 *
 *  Created on: 20/09/2013
 *      Author: drb
 */

#ifndef AREAMAP_H_
#define AREAMAP_H_

#include "../render/sprite.h"
#include "../render/ISprite.h"
#include <vector>

class AreaMap {
public:
	AreaMap();
	AreaMap(AreaMap* Parent , SDL_Rect Area);
	virtual ~AreaMap();

	void insert(ISprite* sp);

	std::vector<ISprite*> getSpritesFromArea (SDL_Rect Area);

	bool remove (ISprite* sp);

	void update (ISprite* sp);

	SDL_Rect getArea();

	void clear();

	int count();

protected:
	SDL_Rect area;
	std::vector<ISprite*>  sprites;
	std::vector<AreaMap> children;
	AreaMap* parent;
private:
	void split();
};

#endif /* AREAMAP_H_ */
