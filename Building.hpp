/*
 * Building.h
 *
 *  Created on: 5 juil. 2012
 *      Author: Erwann
 */

#ifndef BUILDING_H_
#define BUILDING_H_
#include "Entity.hpp"
#include <iostream>

class Character;
class Building: public Entity {
public:
	Building();
	Building(const sf::Texture &Img, const sf::Vector2f &Position=sf::Vector2f(0, 0));
	virtual ~Building();
	void update();
	unsigned int getIntegrity() const;
	unsigned int getMaxIntegrity() const;
	sf::Shape& getIntegrityBar();
	void setIntegrity(unsigned int value);
	void setEntryPoint(int x, int y);
	sf::Vector2f getEntryLocal();
	sf::Vector2f getEntryGlobal();
	bool getConstructed();
	void setOwner(Character* owner);
	Character* getOwner();
	void draw(sf::RenderTarget* sys);
	sf::Vector2i getSize();

protected:
    Character* m_owner;
	bool is_constructed;
	double integrity, integrity_max;
	sf::RectangleShape integrity_bar;
    sf::Vector2f entry;
    sf::Vector2i base_size;
};

#endif /* BUILDING_H_ */
