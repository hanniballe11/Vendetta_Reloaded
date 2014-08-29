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
	Effect(const sf::Texture &Img, unsigned int anims, unsigned int states);
	virtual ~Effect();
	void update();
	unsigned int getState();
	void attachEntity(Entity *entity);
	void setPosition(sf::Vector2f pos);
	void setTexture(sf::Texture &Img);
	bool getActive();
	void activate();
	void draw(sf::RenderTarget* sys);
protected:
	unsigned int current_state, nb_anim, nb_state, random_anim, counter;
	bool is_active;
	Entity *m_entity_attached;
};

#endif /* EFFECT_H_ */
