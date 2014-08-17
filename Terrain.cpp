/*
 * Building.cpp
 *
 *  Created on: 5 juil. 2012
 *      Author: Erwann
 */

#include "Terrain.hpp"

Terrain::Terrain() : sf::RectangleShape(){
}
Terrain::Terrain(const sf::Texture *Img,const sf::Vector2f &Size) : sf::RectangleShape(Size){
    //setPosition(0,0);
    setTexture(Img);
    setTextureRect(sf::IntRect(0,0,Size.x, Size.y));
}
Terrain::~Terrain() {
}
void Terrain::draw(sf::RenderTarget *target){if(target!=0){target->draw(*this);}}
