/*
 * Character.h
 *
 *  Created on: 4 juil. 2012
 *      Author: Erwann
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Entity.hpp"
#include <iostream>
#define COUNTERMAX 15

class Building;
class Character: public Entity {
public:
	Character();
	Character(const sf::Texture &Img, const sf::Vector2f &Position=sf::Vector2f(0, 0));
	virtual ~Character();

	// Actions
		//Basiques
		void goTo(sf::Vector2f Dest);
		void follow(Entity *target);
		void attack(Entity *target);
		void repair(Building *building);
		void enter(Building *building);
		//Accesseurs de statut
		bool isGoingTo();
		bool isAttacking();
		bool isEnterring();
		bool isIndoor();
		bool isFollowing();
		bool isRepairing();
		bool isMoving();
		//Arret action
		void stop();

	virtual void update();
	void setTexture(const sf::Texture& Img);
	float getSpeed();
	void setSpeed(float fspeed);
	unsigned int getLife();
	void setLife(unsigned int value);
	unsigned int getStamina();
	void setStamina(unsigned int value);
	unsigned int getMana();
	void setMana(unsigned int value);
	const sf::Shape& getLifeBar();
	const sf::Shape& getStaminaBar();
	const sf::Shape& getManaBar();
	void takeDamage(double damage);
	bool isDead();
	void virtual draw(sf::RenderTarget *sys);
	Building* getOwner();
	void setOwner(Building *owner);

protected:
	bool is_moving, is_going_to, show_bar, is_following, is_attacking, is_enterring, is_repairing, is_dead, is_indoor;
	Entity *m_target;
	Building *m_owner;
	unsigned int current_anim, counter_anim;
	float speed;
	double life, stamina, mana, life_max, stamina_max, mana_max, regen_stamina, regen_life, regen_mana, base_attack, base_defense;
	sf::RectangleShape life_bar, stamina_bar, mana_bar;
	sf::Vector2f current_goto;
};

#endif /* CHARACTER_H_ */
