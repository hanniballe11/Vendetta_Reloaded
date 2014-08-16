/*
 * Entity.cpp
 *
 *  Created on: 4 juil. 2012
 *      Author: Erwann
 */

#include "Node.hpp"
#include "Entity.hpp"

Entity::Entity() : sf::Sprite() {
	e_type=ENTITY;
	n_parent=0;
}

Entity::Entity(const sf::Texture &Img, sf::Vector2f Position) : sf::Sprite(Img){
	setPosition(Position);
	e_type=ENTITY;
	n_parent=0;
}

Entity::~Entity(){
	if(n_parent!=0){n_parent->remove(this);}
	n_parent=0;
}
void Entity::draw(sf::RenderTarget *sys){
	if(sys!=0){sys->draw(*this);}
}
void Entity::setParent(Node* parent){n_parent=parent;}
Node* Entity::getParent(){return n_parent;}
EntityType Entity::getType(){return e_type;}
