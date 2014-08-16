/*
 * Player.h
 *
 *  Created on: 5 juil. 2012
 *      Author: Erwann
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.hpp"

class Player: public Character {
public:
	Player();
	Player(const sf::Texture &Img, const sf::Vector2f &Position=sf::Vector2f(0, 0));
	virtual ~Player();
	void goUp();
	void goDown();
	void goLeft();
	void goRight();
	void virtual update();
	bool moveBlocked();
	void setBlockedMove(bool state);

protected:
	bool man_move_x, man_move_y;
	bool is_blocked;
};

#endif /* PLAYER_H_ */
