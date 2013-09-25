/*
 * AreaMap.cpp
 *
 *  Created on: 20/09/2013
 *      Author: drb
 */

#include "AreaMap.h"
#include <limits>
#include "vector.h"
#include <iostream>
#include <cassert>
#include <cmath>

AreaMap::AreaMap() {
	// TODO Auto-generated constructor stub
	this->parent = nullptr;
	//Most even spread of all area over the axis
	this->area.x = std::numeric_limits<int>::min()/2;
	this->area.y = std::numeric_limits<int>::min()/2;
	//Maximum amount of area possible
	this->area.h = std::numeric_limits<int>::max();
	this->area.w = std::numeric_limits<int>::max();

	children.reserve(4);
	sprites.reserve (10);
}

AreaMap::~AreaMap() {
	// TODO Auto-generated destructor stub
	this->clear();
}

AreaMap::AreaMap(AreaMap* Parent , SDL_Rect Area) {
	this->parent = Parent;
	this->area = Area;
}

void AreaMap::insert(sprite* sp) {
	if (this->sprites.size() > 4 || this->children.size() == 4) {
		//Haven't split yet, might as well
		if (this->children.size() != 4) {
			this->split();
		}
		//Go through children to see if they want it
		for (unsigned int n = 0; n < this->children.size(); n++) {
			//Check if the sprite belongs to this child's area
			if ( isWholeRectInside( sp->getBounds() , this->children[n].getArea() ) ) {
				this->children[n].insert(sp);
				return;
			}
		}
	}
	//Gives up on passing onto the children and keeps it
	this->sprites.push_back(sp);
}
std::vector<sprite*> AreaMap::getSpritesFromArea (SDL_Rect Area) {
	std::vector<sprite*> output;
	for (unsigned int i = 0; i < this->sprites.size(); i++) {
		if ( isRectTouching( this->sprites[i]->getBounds() , Area ) ) {
			output.push_back(this->sprites[i]);
		}
	}
	for (unsigned int n = 0; n < this->children.size(); n++) {
		//Make sure the child has a chance of having the area
		if ( isRectTouching( this->children[n].getArea() , Area ) ) {
			std::vector<sprite*> sp = this->children[n].getSpritesFromArea(Area);
			output.insert(output.end(), sp.begin(), sp.end());
		}
	}
	return output;
}

SDL_Rect AreaMap::getArea() {
	return this->area;
}

void AreaMap::split() {
	//If there are no children, time to make some
	if (children.size() == 0)
	{
		SDL_Rect new_area;
		//Width and height will remain const
		new_area.w = this->area.w/2;
		new_area.h = this->area.h/2;
		//Position of the rect will change to the four sections

		//Top left
		new_area.x = this->area.x; new_area.y = this->area.y;
		this->children.push_back( AreaMap( this ,  new_area ) );

		//Top right
		new_area.x = this->area.x + new_area.w; new_area.y = this->area.y;
		this->children.push_back( AreaMap( this ,  new_area ) );

		//bottom left
		new_area.x = this->area.x ; new_area.y = this->area.y + new_area.h;
		this->children.push_back( AreaMap( this ,  new_area ) );

		//bottom right
		new_area.x = this->area.x + new_area.w; new_area.y = this->area.y + new_area.h;
		this->children.push_back( AreaMap( this ,  new_area ) );
	}
	std::vector<sprite*> leftovers;
	for (unsigned int i = 0; i < this->sprites.size(); i++) {
		//Keep track of sprites that are not giving to children
		bool taken = false;
		for (unsigned int n = 0; n < this->children.size(); n++) {
			//Check if the sprite belongs to this child's area
			if ( isWholeRectInside( sprites[i]->getBounds() ,this->children[n].getArea() ) ) {
				this->children[n].insert(sprites[i]);
				taken = true;
			}
		}
		if (!taken) {
			leftovers.push_back(sprites[i]);
		}
	}
	this->sprites = leftovers;
}

void AreaMap::clear() {
	this->sprites.clear();
	for (unsigned int n = 0; n < this->children.size(); n++) {
		this->children[n].clear();
	}
	this->children.clear();
}
