/*
 * Object.cpp
 *
 *  Created on: 15 juil. 2012
 *      Author: Erwann
 */

#include "Object.hpp"

Object::Object() : Entity(){
	e_type=OBJECT;
	infinite=false;
	nb_use=0;
	max_use=1;
}
Object::Object(const sf::Texture &Img, std::string data, const sf::Vector2f &Position) : Entity(Img, Position){
	e_type=OBJECT;
	infinite=false;
	nb_use=0;
	max_use=1;
	data_values=data;
}
Object::~Object() {

}
bool Object::isInfinite(){return infinite;}
void Object::setInfinite(bool value){infinite=value;}
unsigned int Object::getUse(){return nb_use;}
void Object::setUse(unsigned int value){nb_use=value;}
unsigned int Object::getUseMax(){return max_use;}
void Object::setUseMax(unsigned int value){max_use=value;}
bool Object::use(Character *user, Character *opponent){
	if(user!=0){
		return true;
	}
	else{return false;}
}
