/*
 * Character.cpp
 *
 *  Created on: 4 juil. 2012
 *      Author: Erwann
 */

#include "Character.hpp"
#include "Building.hpp"

Character::Character() : Entity(){
	e_type=CHARACTER;
	m_target=0;
	current_goto.x=-1;
	current_goto.y=-1;
	current_anim=0;
	counter_anim=0;
	is_moving=false;
	is_going_to=false;
	is_following=false;
	is_attacking=false;
	is_indoor=false;
	is_enterring=false;
	is_repairing=false;
	is_dead=false;
	show_bar=true;
	m_owner=0;
	m_building_in=0;

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
	is_moving=false;
	is_going_to=false;
	is_following=false;
	is_attacking=false;
	is_indoor=false;
	is_enterring=false;
	is_repairing=false;
	setTextureRect(sf::IntRect(0,0,getTexture()->getSize().x/4, getTexture()->getSize().y/4));
	is_dead=false;
	show_bar=true;
	m_owner=0;
	m_building_in=0;

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
unsigned int Character::getLife(){return m_current_life;}
const sf::Shape& Character::getLifeBar(){return life_bar;}
unsigned int Character::getMana(){return m_current_mana;}
const sf::Shape& Character::getManaBar(){return mana_bar;}
float Character::getSpeed(){return m_race.base_speed;}
unsigned int Character::getStamina(){return m_current_stamina;}
const sf::Shape& Character::getStaminaBar(){return stamina_bar;}
void Character::setTexture(const sf::Texture& Img){
	sf::Sprite::setTexture(Img);
	setTextureRect(sf::IntRect(0,0,getTexture()->getSize().x/4, getTexture()->getSize().y/4));
}
void Character::setLife(unsigned int value){if(value>=0 && value<=m_race.base_life){m_current_life=value;}}
void Character::setMana(unsigned int value){if(value>=0 && value<=m_race.base_mana){m_current_mana=value;}}
void Character::setStamina(unsigned int value){if(value>=0 && value<=m_race.base_stamina){m_current_stamina=value;}}
// Actions
		//Basiques
void Character::goTo(sf::Vector2f Dest){
	stop();
	current_goto=Dest;
	is_going_to=true;
}
void Character::orderToFollow(Entity *target){
	if(target && (target->getType()==CHARACTER || target->getType()==PLAYER || target->getType()==BUILDING)){
		stop();
		current_goto=target->getPosition();
		m_target=target;
		is_following=true;}
}
void Character::orderToAttack(Entity *target){
	if(target && (target->getType()==CHARACTER || target->getType()==PLAYER || target->getType()==BUILDING)){
		orderToFollow(target);
		is_attacking=true;}
}
void Character::orderToEnter(Building *building){
    if(building!=0){
		stop();
        if(building->getConstructed()){
                is_enterring=true;
                current_goto.x=building->getEntryGlobal().x-getTextureRect().width/2;
                current_goto.y=building->getEntryGlobal().y;
                m_target=building;
        }
        else if(m_owner==building){orderToRepair(building);}}
}
void Character::orderToRepair(Building *building){
    if(building!=0){
		stop();
        is_repairing=true;
        current_goto.x=building->getEntryGlobal().x-getTextureRect().width/2;
        current_goto.y=building->getEntryGlobal().y;
        m_target=building;
        }
}

void Character::attack(Character *target)
{
    if(m_current_stamina==m_race.base_stamina && target!=0){
            if(target->getLife()>0){
                    target->takeDamage(m_race.base_attack);
                    m_current_stamina=0;
                    is_attacking=true;}
            else{is_attacking=false;}}
}
void Character::attack(Building *target)
{
    if(m_current_stamina==m_race.base_stamina && target!=0){
            if(target->getIntegrity()>0){
                    target->takeDamage(m_race.base_attack);
                    m_current_stamina=0;
                    is_attacking=true;}
            else{is_attacking=false;}}
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
	m_building_in=0;
}
void Character::update(){
	sf::Vector2f current_pos=getPosition();
	sf::Vector2f current_move;
	//ACTIONS
	if(current_goto.x==-1 && current_goto.y==-1){
        if(is_going_to){is_going_to=false;}
        else if(is_enterring){is_indoor=true; m_building_in=dynamic_cast<Building*>(m_target);}
        else if(is_repairing){dynamic_cast<Building*>(m_target)->repair(1);}
	}
    if(is_following){current_goto=m_target->getPosition();}
    if(is_attacking && getGlobalBounds().intersects(m_target->getGlobalBounds())){
            if(m_target->getType()==CHARACTER || m_target->getType()==PLAYER || m_target->getType()==BUILDING){
				    current_goto.x=-1;
					current_goto.y=-1;
					if(m_target->getType()==BUILDING){
                        Building *temp_target=dynamic_cast<Building*>(m_target);
                        attack(temp_target);}
                    else{
                        Character *temp_target=dynamic_cast<Character*>(m_target);
                        attack(temp_target);}}
    }
	//GESTION DEPLACEMENT ( VITESSE, ETC... )
	if(current_goto.x!=-1 && current_goto.y!=-1 && current_goto!=current_pos){
				if(abs(current_goto.x-current_pos.x)>=m_race.base_speed){current_move.x=(current_goto.x-current_pos.x)/abs(current_goto.x-current_pos.x)*m_race.base_speed;}
				else{current_move.x=current_goto.x-current_pos.x;}
				if(abs(current_goto.y-current_pos.y)>=m_race.base_speed){current_move.y=(current_goto.y-current_pos.y)/abs(current_goto.y-current_pos.y)*m_race.base_speed;}
				else{current_move.y=current_goto.y-current_pos.y;}
				//CORRECTION DEPLACEMENT EN DIAGONALE
				if(current_move.x!=0 && current_move.y!=0){
					if(abs(current_move.x)==m_race.base_speed){current_move.x=current_move.x*0.7f;}
					if(abs(current_move.y)==m_race.base_speed){current_move.y=current_move.y*0.7f;}
				}
				counter_anim++;
				is_moving=true;
				move(current_move);
	}
	else{is_moving=false; current_anim=0; counter_anim=0; current_goto.x=-1; current_goto.y=-1;}
	unsigned int direction=0;
	if(is_moving){
		if(current_move.x!=0.f){
			if(current_move.x>0.f){direction=2;}
			else{direction=1;}
		}
		else if(current_move.y<0.f){direction=3;}
		else{;}
		if(counter_anim>=COUNTERMAX){
			if(current_anim>=3){current_anim=0;}
			else{current_anim++;}
			counter_anim=0;
		}
	}
	setTextureRect(sf::IntRect(current_anim*(getTexture()->getSize().x/4), direction*(getTexture()->getSize().y/4), getTexture()->getSize().x/4, getTexture()->getSize().y/4));
	if(!is_dead){
	m_race.base_life-m_current_life<m_race.base_life/5000 ? m_current_life+=m_race.base_life-m_current_life: m_current_life+=m_race.base_life/5000;
	m_race.base_stamina-m_current_stamina<m_race.base_stamina/50 ? m_current_stamina+=m_race.base_stamina-m_current_stamina : m_current_stamina+=m_race.base_stamina/50;
	m_race.base_mana-m_current_mana<m_race.base_mana/2000 ? m_current_mana+=m_race.base_mana-m_current_mana: m_current_mana+=m_race.base_mana/2000;
	}
	life_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height-2);
	life_bar.setSize(sf::Vector2f(getTextureRect().width*(m_current_life/m_race.base_life), 2));
	stamina_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height+2);
	stamina_bar.setSize(sf::Vector2f(getTextureRect().width*(m_current_stamina/m_race.base_stamina), 2));
	mana_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height+6);
	mana_bar.setSize(sf::Vector2f(getTextureRect().width*(m_current_mana/m_race.base_mana), 2));
}
void Character::takeDamage(double damage){
	m_current_life-damage<0 ? m_current_life=0 : m_current_life-=damage;
	if(m_current_life==0){is_dead=true;}
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

void Character::setRace(Race race)
{
    m_race=race;
    m_current_life=race.base_life;
    m_current_stamina=race.base_stamina;
    m_current_mana=race.base_mana;
}

Race Character::getRace(){return m_race;}

Building* Character::getBuildingIn(){return m_building_in;}
