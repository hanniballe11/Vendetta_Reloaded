/*
 * Projectile.cpp
 *
 *  Created on: 15 juil. 2012
 *      Author: Erwann
 */

#include "Projectile.hpp"

Projectile::Projectile() : Entity(){
	e_type=PROJECTILE;
	range=0.f;
	speed=0.f;
	current_distance=0.f;
	is_out_of_range=true;
}
Projectile::Projectile(const sf::Texture &Img, unsigned int states, const sf::Vector2f &Position) : Entity(Img, Position){
	e_type=PROJECTILE;
	range=30.f;
	speed=1.f;
	current_distance=0.f;
	is_out_of_range=false;

}
Projectile::~Projectile() {

}
void Projectile::sendTo(sf::Vector2f pos){
	sf::Vector2f relative_pos=getPosition()-pos;
	coef_direction.x=relative_pos.x/(relative_pos.x+relative_pos.y);
	coef_direction.y=relative_pos.y/(relative_pos.x+relative_pos.y);
}
void Projectile::update(){
	// Animation
	if(current_distance<range-speed){
		move(coef_direction.x*speed, coef_direction.y*speed);
		current_distance+=sqrt(pow(coef_direction.x,2)+pow(coef_direction.y,2))*speed;
	}
	else if(current_distance>range-speed && current_distance<range){
		move(coef_direction.x*range-speed, coef_direction.y*range-speed);
		current_distance=range;
	}
	else{is_out_of_range=true;}
}
bool Projectile::isOutOfRange(){return is_out_of_range;}
