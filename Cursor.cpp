/*
 * Cursor.cpp
 *
 *  Created on: 15 juil. 2012
 *      Author: Erwann
 */

#include "Cursor.hpp"

Cursor::Cursor() : Entity(){
	e_type=SYSTEM;
	// TODO Auto-generated constructor stub

}
Cursor::Cursor(const sf::Texture &Img, const sf::Vector2f &Position) : Entity(Img, Position){
	e_type=SYSTEM;
	// TODO Auto-generated constructor stub

}
Cursor::~Cursor() {
	// TODO Auto-generated destructor stub
}

void Cursor::setCursorPosition(float x, float y){
	setPosition(x, y);
}
void Cursor::setCursorPosition(sf::Vector2f position){
    setPosition(position);
}
void Cursor::setIcon(const sf::Texture &img){
	setTexture(img);
}
const sf::Texture* Cursor::getIcon(){
	return getTexture();
}
