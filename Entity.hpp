/*
 * Entity.h
 *
 *  Created on: 4 juil. 2012
 *      Author: Erwann
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics.hpp>
#include <cstdlib>
//#include "Node.hpp"
enum EntityType{
	ENTITY,
	CHARACTER,
	PLAYER,
	BUILDING,
	EFFECT,
	OBJECT,
	PROJECTILE,
	SYSTEM
};
class Node;
class Entity: public sf::Sprite {
public:
	Entity();
	Entity(const sf::Texture &Img, sf::Vector2f Position=sf::Vector2f(0,0));
	virtual ~Entity();
	void virtual draw(sf::RenderTarget *sys);
	void setParent(Node* parent);
	Node* getParent();
	EntityType getType();

protected:
	EntityType e_type;
	Node* n_parent;
};

#endif /* ENTITY_H_ */
