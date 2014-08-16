/*
 * Player.cpp
 *
 *  Created on: 5 juil. 2012
 *      Author: Erwann
 */

#include "Player.hpp"

Player::Player() : Character(){
	man_move_x=false;
	man_move_y=false;
	is_blocked=false;
	e_type=PLAYER;
}
Player::Player(const sf::Texture &Img, const sf::Vector2f &Position) : Character(Img, Position){
	man_move_x=false;
	man_move_y=false;
	is_blocked=false;
	e_type=PLAYER;
}
Player::~Player() {

}
void Player::goUp(){
	if(!is_blocked){
	current_goto.y=getPosition().y-speed;
	man_move_y=true;
	if(!man_move_x){current_goto.x=getPosition().x;}}
}
void Player::goDown(){
	if(!is_blocked){
	current_goto.y=getPosition().y+speed;
	man_move_y=true;
	if(!man_move_x){current_goto.x=getPosition().x;}}
}
void Player::goLeft(){
	if(!is_blocked){
	current_goto.x=getPosition().x-speed;
	man_move_x=true;
	if(!man_move_y){current_goto.y=getPosition().y;}}
}
void Player::goRight(){
	if(!is_blocked){
	current_goto.x=getPosition().x+speed;
	man_move_x=true;
	if(!man_move_y){current_goto.y=getPosition().y;}}
}
void Player::update(){
	Character::update();
	man_move_x=false;
	man_move_y=false;
}

bool Player::moveBlocked(){return is_blocked;}
void Player::setBlockedMove(bool state){is_blocked=state;}
