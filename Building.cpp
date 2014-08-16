/*
 * Building.cpp
 *
 *  Created on: 5 juil. 2012
 *      Author: Erwann
 */

#include "Building.hpp"
#include "Character.hpp"

Building::Building() : Entity(){
	e_type=BUILDING;
	is_constructed=false;
	m_owner=0;
	entry=sf::Vector2f(0,0);
	integrity=1.0;
	integrity_max=1000.0;

	integrity_bar.setSize(sf::Vector2f(getTextureRect().width, 2));
	integrity_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height-2);
	integrity_bar.setFillColor(sf::Color(0,255,0));
	integrity_bar.setOutlineColor(sf::Color(0,0,0));
	integrity_bar.setOutlineThickness(2.f);
}
Building::Building(const sf::Texture &Img, const sf::Vector2f &Position) : Entity(Img, Position) {
	e_type=BUILDING;
	is_constructed=false;
	m_owner=0;
	entry=sf::Vector2f(0,0);
	integrity=1.0;
	integrity_max=1000.0;
	setTextureRect(sf::IntRect(0, 0, getTexture()->getSize().x/2, getTexture()->getSize().y/4));
	integrity_bar.setSize(sf::Vector2f(getTextureRect().width, 2));
	integrity_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height-2);
	integrity_bar.setFillColor(sf::Color(0,255,0));
	integrity_bar.setOutlineColor(sf::Color(0,0,0));
	integrity_bar.setOutlineThickness(2.f);
}
Building::~Building() {
    m_owner=0;
    delete m_owner;
}
void Building::update(){
	unsigned int current_state=3;
	double ratio_integrity=(double)(integrity)/(double)(integrity_max);
	if(ratio_integrity>0.75){current_state=0;}
	else if(ratio_integrity>0.5){current_state=1;}
	else if(ratio_integrity>0.25){current_state=2;}
	else{current_state=3;}
	setTextureRect(sf::IntRect(getTexture()->getSize().x/2*(int)(is_constructed), getTexture()->getSize().y/4*current_state, getTexture()->getSize().x/2, getTexture()->getSize().y/4));
	integrity_bar.setSize(sf::Vector2f(getTextureRect().width*ratio_integrity, 2));
	integrity_bar.setPosition(getPosition().x, getPosition().y+getTextureRect().height-2);
}
unsigned int Building::getIntegrity() const{return integrity;}
sf::Shape& Building::getIntegrityBar(){return integrity_bar;}
void Building::setIntegrity(unsigned int value){
    if(value>integrity_max){integrity=integrity_max;}
    else if(value<0){integrity=0;}
	else{integrity=value;}
	if(integrity==integrity_max && !is_constructed){is_constructed=true;}
}
unsigned int Building::getMaxIntegrity() const{return integrity_max;}
void Building::setEntryPoint(int x, int y){
    entry.x=x;
    entry.y=y;
}
sf::Vector2f Building::getEntryLocal(){return entry;}
sf::Vector2f Building::getEntryGlobal(){return entry+getPosition();}
bool Building::getConstructed(){return is_constructed;}
void Building::setOwner(Character* owner){m_owner=owner;}
Character* Building::getOwner(){return m_owner;}
void Building::draw(sf::RenderTarget *sys){if(sys!=0){
sys->draw(*this);
if(integrity!=integrity_max){sys->draw(integrity_bar);}}}
