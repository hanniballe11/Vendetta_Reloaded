/*
 * Projectile.h
 *
 *  Created on: 6 juil. 2012
 *      Author: Erwann
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "Entity.hpp"
#include <math.h>

class Projectile : public Entity {
public:
	Projectile();
	Projectile(const sf::Texture &Img, unsigned int states, const sf::Vector2f &Position=sf::Vector2f(0, 0));
	virtual ~Projectile();
	void sendTo(sf::Vector2f pos);
	void update();
	bool isOutOfRange();

protected:
	float speed, range,  current_distance;
	bool is_out_of_range;
	sf::Vector2f coef_direction;

};

#endif /* PROJECTILE_H_ */
