/*
 * Cursor.h
 *
 *  Created on: 15 juil. 2012
 *      Author: Erwann
 */

#ifndef CURSOR_H_
#define CURSOR_H_

#include "Entity.hpp"

class Cursor: public Entity {
public:
	Cursor();
	Cursor(const sf::Texture &Img, const sf::Vector2f &Position=sf::Vector2f(0, 0));
	virtual ~Cursor();
	void setCursorPosition(float x, float y);
	void setCursorPosition(sf::Vector2f position);
	void setIcon(const sf::Texture &img);
	const sf::Texture* getIcon();
};

#endif /* CURSOR_H_ */
