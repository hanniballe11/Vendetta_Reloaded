/*
 * Character.cpp
 *
 *  Created on: 4 juil. 2012
 *      Author: Erwann
 */

#include "Character.hpp"
#include "Building.hpp"
#include <iostream>

Character::Character() : Entity(){
	e_type=CHARACTER;
	m_target=0;
	current_goto.x=-1;
	current_goto.y=-1;
	current_anim=0;
	counter_anim=0;
	speed=3.f;
	is_moving=false;
	is_going_to=false;
	is_following=false;
	is_attacking=false;
	is_indoor=false;
	is_enterring=false;
	is_repairing=false;
	life=100.0;
	stamina=100.0;
	mana=100.0;
	life_max=100.0;
	stamina_max=100.0;
	mana_max=100.0;
	is_dead=false;
	regen_stamina=2.0;
	regen_life=0.2;
	regen_mana=0.5;
	base_attack=5.0;
	base_defense=0.0;
	show_bar=true;
	m_owner=0;

	life_bar.setSize(sf::Vector2f(getTextureRect().width, 2));
	life_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height-2);
	life_bar.setFillColor(sf::Color(255,0,0));
	life_bar.setOutlineColor(sf::Color(0,0,0));
	life_bar.setOutlineThickness(2.f);
	stamina_bar.setSize(sf::Vector2f(getTextureRect().width, 2));
	stamina_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height+2);
	stamina_bar.setFillColor(sf::Color(255,255,255));
	stamina_bar.setOutlineColor(sf::Color(0,0,0));
	stamina_bar.setOutlineThickness(2.f);
	mana_bar.setSize(sf::Vector2f(getTextureRect().width, 2));
	mana_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height+6);
	mana_bar.setFillColor(sf::Color(0,0,255));
	mana_bar.setOutlineColor(sf::Color(0,0,0));
	mana_bar.setOutlineThickness(2.f);
}
Character::Character(const sf::Texture &Img, const sf::Vector2f &Position) : Entity(Img, Position){
	e_type=CHARACTER;
	m_target=0;
	current_goto.x=-1;
	current_goto.y=-1;
	current_anim=0;
	counter_anim=0;
	speed=3.f;
	is_moving=false;
	is_going_to=false;
	is_following=false;
	is_attacking=false;
	is_indoor=false;
	is_enterring=false;
	is_repairing=false;
	setTextureRect(sf::IntRect(0,0,getTexture()->getSize().x/4, getTexture()->getSize().y/4));
	life=100.0;
	stamina=100.0;
	mana=100.0;
	life_max=100.0;
	stamina_max=100.0;
	mana_max=100.0;
	is_dead=false;
	regen_stamina=stamina_max/50.0;
	regen_life=life_max/5000.0;
	regen_mana=mana_max/500.0;
	base_attack=5.0;
	base_defense=0.0;
	show_bar=true;
	m_owner=0;

	life_bar.setSize(sf::Vector2f(getTextureRect().width, 2));
	life_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height-2);
	life_bar.setFillColor(sf::Color(255,0,0));
	life_bar.setOutlineColor(sf::Color(0,0,0));
	life_bar.setOutlineThickness(2.f);
	stamina_bar.setSize(sf::Vector2f(getTextureRect().width, 2));
	stamina_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height+2);
	stamina_bar.setFillColor(sf::Color(255,255,255));
	stamina_bar.setOutlineColor(sf::Color(0,0,0));
	stamina_bar.setOutlineThickness(2.f);
	mana_bar.setSize(sf::Vector2f(getTextureRect().width, 2));
	mana_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height+6);
	mana_bar.setFillColor(sf::Color(0,0,255));
	mana_bar.setOutlineColor(sf::Color(0,0,0));
	mana_bar.setOutlineThickness(2.f);
}
Character::~Character(){;}
unsigned int Character::getLife(){return life;}
const sf::Shape& Character::getLifeBar(){return life_bar;}
unsigned int Character::getMana(){return mana;}
const sf::Shape& Character::getManaBar(){return mana_bar;}
float Character::getSpeed(){return speed;}
unsigned int Character::getStamina(){return stamina;}
const sf::Shape& Character::getStaminaBar(){return stamina_bar;}
void Character::setTexture(const sf::Texture& Img){
	sf::Sprite::setTexture(Img);
	setTextureRect(sf::IntRect(0,0,getTexture()->getSize().x/4, getTexture()->getSize().y/4));
}
void Character::setLife(unsigned int value){if(value>=0 && value<=life_max){life=value;}}
void Character::setMana(unsigned int value){if(value>=0 && value<=mana_max){mana=value;}}
void Character::setSpeed(float fspeed){speed=fspeed;}
void Character::setStamina(unsigned int value){if(value>=0 && value<=stamina_max){stamina=value;}}
// Actions
		//Basiques
void Character::goTo(sf::Vector2f Dest){
	stop();
	current_goto=Dest;
	is_going_to=true;
}
void Character::follow(Entity *target){
	if(target && (target->getType()==CHARACTER || target->getType()==PLAYER || target->getType()==BUILDING)){
		stop();
		current_goto=target->getPosition();
		m_target=target;
		is_following=true;}
}
void Character::attack(Entity *target){
	if(target && (target->getType()==CHARACTER || target->getType()==PLAYER || target->getType()==BUILDING)){
		follow(target);
		is_attacking=true;}
}
void Character::enter(Building *building){
    if(building!=0){
		stop();
        is_enterring=true;
        current_goto.x=building->getEntryGlobal().x-getTextureRect().width/2;
        current_goto.y=building->getEntryGlobal().y;
        m_target=building;
        }
}
void Character::repair(Building *building){
    if(building!=0){
		stop();
        is_repairing=true;
        current_goto.x=building->getEntryGlobal().x-getTextureRect().width/2;
        current_goto.y=building->getEntryGlobal().y;
        m_target=building;
        }
}
		//Accesseurs de statut
bool Character::isMoving(){return is_moving;}
bool Character::isGoingTo(){return is_going_to;}
bool Character::isAttacking(){return is_attacking;}
bool Character::isEnterring(){return is_enterring;}
bool Character::isIndoor(){return is_indoor;}
bool Character::isFollowing(){return is_following;}
bool Character::isRepairing(){return is_repairing;}
		//Arret action
void Character::stop(){
	current_goto.x=-1;
	current_goto.y=-1;
	current_anim=0;
	counter_anim=0;
	is_going_to=false;
	is_attacking=false;
	is_enterring=false;
	is_following=false;
	is_repairing=false;
	is_indoor=false;
}
void Character::update(){
	sf::Vector2f current_pos=getPosition();
	sf::Vector2f current_move;
	//ACTIONS
	if(is_going_to){if(current_goto.x==-1 && current_goto.y==-1){is_going_to=false;}}
	else if(is_following){
		current_goto.x=m_target->getPosition().x; current_goto.y=m_target->getPosition().y;
		if(is_attacking && getGlobalBounds().intersects(m_target->getGlobalBounds())){
			if(m_target->getType()==CHARACTER || m_target->getType()==PLAYER || m_target->getType()==BUILDING){
				    current_goto.x=-1;
					current_goto.y=-1;
					if(m_target->getType()==BUILDING){
                        Building *temp_target=dynamic_cast<Building*>(m_target);
                        if(temp_target->getIntegrity()>0){
                            if(stamina==stamina_max){temp_target->setIntegrity(temp_target->getIntegrity()-10); stamina=0;}}
                        else{is_attacking=!is_attacking;}}
                    else{
                        Character *temp_target=dynamic_cast<Character*>(m_target);
                        if(!temp_target->isDead()){
                            if(stamina==stamina_max){temp_target->takeDamage(base_attack); stamina=0;}}
                        else{is_attacking=!is_attacking;}
                    }}}}
	else if(is_attacking){
		if(m_target->getType()==CHARACTER || m_target->getType()==PLAYER){
				if(getGlobalBounds().intersects(m_target->getGlobalBounds()) && !dynamic_cast<Character*>(m_target)->isDead()){
					if(stamina==stamina_max){dynamic_cast<Character*>(m_target)->takeDamage(base_attack); stamina=0;}}}
			else if(m_target->getType()==BUILDING){
				if(getGlobalBounds().intersects(m_target->getGlobalBounds()) && dynamic_cast<Building*>(m_target)->getIntegrity()!=0){
					if(stamina==stamina_max){dynamic_cast<Building*>(m_target)->setIntegrity(dynamic_cast<Building*>(m_target)->getIntegrity()-10); stamina=0;}}}
			else{;}}
	else if(is_enterring && (current_goto.x==-1 && current_goto.y==-1)){
		is_indoor=true;}
	else if(is_repairing && (current_goto.x==-1 && current_goto.y==-1)){
		dynamic_cast<Building*>(m_target)->setIntegrity(dynamic_cast<Building*>(m_target)->getIntegrity()+1);}
	//GESTION DEPLACEMENT ( VITESSE, ETC... )
	if(current_goto.x!=-1 && current_goto.y!=-1){
			if(current_goto!=current_pos){
				if(abs(current_goto.x-current_pos.x)>=speed){current_move.x=(current_goto.x-current_pos.x)/abs(current_goto.x-current_pos.x)*speed;}
				else{current_move.x=current_goto.x-current_pos.x;}
				if(abs(current_goto.y-current_pos.y)>=speed){current_move.y=(current_goto.y-current_pos.y)/abs(current_goto.y-current_pos.y)*speed;}
				else{current_move.y=current_goto.y-current_pos.y;}
				//CORRECTION DEPLACEMENT EN DIAGONALE
				if(current_move.x!=0 && current_move.y!=0){
					if(abs(current_move.x)==speed){current_move.x=current_move.x*0.7f;}
					if(abs(current_move.y)==speed){current_move.y=current_move.y*0.7f;}
				}
				counter_anim++;
				is_moving=true;
			}
			else{
				is_moving=false;
				current_goto.x=-1;
				current_goto.y=-1;
				current_anim=0;
				counter_anim=0;}
	}
	else{is_moving=false; current_anim=0; counter_anim=0;}
	move(current_move);
	unsigned int direction=0;
	if(is_moving){
		if(current_move.x!=0.f){
			if(current_move.x>0.f){direction=2;}
			else{direction=1;}
		}
		else if(current_move.y>0.f){direction=0;}
		else if(current_move.y<0.f){direction=3;}
		if(counter_anim>=COUNTERMAX){
			if(current_anim>=3){current_anim=0;}
			else{current_anim++;}
			counter_anim=0;
		}
	}
	setTextureRect(sf::IntRect(current_anim*(getTexture()->getSize().x/4), direction*(getTexture()->getSize().y/4), getTexture()->getSize().x/4, getTexture()->getSize().y/4));
	if(!is_dead){
	life_max-life<regen_life? life+=life_max-life: life+=regen_life;
	stamina_max-stamina<regen_stamina ? stamina+=stamina_max-stamina : stamina+=regen_stamina;
	mana_max-mana<regen_mana? mana+=mana_max-mana: mana+=regen_mana;
	}
	life_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height-2);
	life_bar.setSize(sf::Vector2f(getTextureRect().width*(life/life_max), 2));
	stamina_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height+2);
	stamina_bar.setSize(sf::Vector2f(getTextureRect().width*(stamina/stamina_max), 2));
	mana_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height+6);
	mana_bar.setSize(sf::Vector2f(getTextureRect().width*(mana/mana_max), 2));
}
void Character::takeDamage(double damage){
	life-damage<0 ? life=0 : life-=damage;
	if(life==0){is_dead=true;}
}
bool Character::isDead(){return is_dead;}
void Character::draw(sf::RenderTarget *sys){
	if(sys!=0 && !is_indoor){
		sys->draw(*this);
		sys->draw(life_bar);
		sys->draw(mana_bar);
		sys->draw(stamina_bar);}
}

Building* Character::getOwner(){return m_owner;}
void Character::setOwner(Building* owner){if(owner){m_owner=owner; owner->setOwner(this);}}
