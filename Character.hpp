/*
 * Character.h
 *
 *  Created on: 4 juil. 2012
 *      Author: Erwann
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <iostream>
#include <vector>
#include "Entity.hpp"
#include "Object.hpp"
#define COUNTERMAX 15

typedef struct Race
{
    std::string name;
    double base_attack;
    double base_defense;
    double base_stamina;
    double base_mana;
    double base_life;
    float base_speed;
};

//class Object;
class Building;
class Character: public Entity {
public:
	Character();
	Character(const sf::Texture &Img, const sf::Vector2f &Position=sf::Vector2f(0, 0));
	virtual ~Character();

	// Actions
		//Basiques
		void goTo(sf::Vector2f Dest);
		void orderToFollow(Entity *target);
		void orderToAttack(Entity *target);
		void orderToRepair(Building *building);
		void orderToEnter(Building *building);

		void attack(Character *target);
		void attack(Building *target);

		///Accesseurs de statut
		bool isGoingTo();
		bool isAttacking();
		bool isEnterring();
		bool isIndoor();
		bool isFollowing();
		bool isRepairing();
		bool isMoving();
		///Arret action
		void stop();

	unsigned int    getLife();
	unsigned int    getStamina();
	unsigned int    getMana();
	float           getSpeed();
	unsigned int    getAttack();
	unsigned int    getDefense();
	Building*       getOwner();
	Building*       getBuildingIn();
	Race            getRace();

	void            setLife(unsigned int value);
	void            setStamina(unsigned int value);
	void            setMana(unsigned int value);
	void            setAttack(unsigned int value);
	void            setDefense(unsigned int value);
	void            setOwner(Building *owner);
	void            setRace(Race race);

	void takeDamage(double damage);

	bool isDead();

	virtual void update();
	void virtual draw(sf::RenderTarget *sys);
	void setTexture(const sf::Texture& Img);

	const sf::Shape& getLifeBar();
	const sf::Shape& getStaminaBar();
	const sf::Shape& getManaBar();

protected:
	bool is_moving, is_going_to, show_bar, is_following, is_attacking, is_enterring, is_repairing, is_dead, is_indoor;
	Entity *m_target;
	Building *m_owner, *m_building_in;
	unsigned int current_anim, counter_anim;
	double m_current_life, m_current_stamina, m_current_mana;
	sf::RectangleShape life_bar, stamina_bar, mana_bar;
	sf::Vector2f current_goto;
	Race m_race;
	std::vector<Object> m_inventory;
};

#endif /* CHARACTER_H_ */
