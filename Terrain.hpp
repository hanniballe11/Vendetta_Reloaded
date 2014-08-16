/*
 * Building.h
 *
 *  Created on: 5 juil. 2012
 *      Author: Erwann
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_
#include "SFML/Graphics.hpp"
#include <iostream>

class Terrain: public sf::RectangleShape{
public:
	Terrain();
	Terrain(const sf::Texture *Img,const sf::Vector2f &Size);
	virtual ~Terrain();
	void draw(sf::RenderTarget *target);

protected:
};

#endif /* TERRAIN_H_ */
