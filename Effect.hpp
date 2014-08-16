/*
 * Effect.h
 *
 *  Created on: 6 juil. 2012
 *      Author: Erwann
 */

#ifndef EFFECT_H_
#define EFFECT_H_

#include "Entity.hpp"
#include "Event.hpp"
#include <cstdlib>

#define COUNTERMAX 5

class Effect: public Entity {
public:
	Effect();
	Effect(const sf::Texture &Img, unsigned int anims, unsigned int states, const sf::Vector2f &Position=sf::Vector2f(0, 0));
	virtual ~Effect();
	void update();
	unsigned int getState();
	void setTexture(sf::Texture &Img);
	bool getActive();
	void activate();
	void draw(sf::RenderTarget* sys);
protected:
	unsigned int current_state, nb_anim, nb_state, random_anim, counter;
	bool is_active;
};

#endif /* EFFECT_H_ */
