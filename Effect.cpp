/*
 * Effect.cpp
 *
 *  Created on: 6 juil. 2012
 *      Author: Erwann
 */

#include "Effect.hpp"

Effect::Effect()
{
    current_state=0;
    nb_anim=0;
    nb_state=0;
    random_anim=0;
    is_active=false;
    counter=0;
}
Effect::Effect(const sf::Texture &Img, unsigned int anims, unsigned int states) : Entity(Img, sf::Vector2f(0,0))
{
    current_state=0;
    nb_anim=anims;
    nb_state=states;
    random_anim=rand() % nb_anim;
    setTextureRect(sf::IntRect(getTexture()->getSize().x/nb_anim*random_anim,getTexture()->getSize().y/nb_state*current_state, getTexture()->getSize().x/nb_anim, getTexture()->getSize().y/nb_state));
    current_state++;
    is_active=true;
    counter=0;
}
Effect::~Effect()
{

}
void Effect::update()
{
    if(counter==COUNTERMAX)
    {
        if(current_state<nb_state)
        {
            setTextureRect(sf::IntRect(getTexture()->getSize().x/nb_anim*random_anim,getTexture()->getSize().y/nb_state*current_state, getTexture()->getSize().x/nb_anim, getTexture()->getSize().y/nb_state));
            current_state++;
            is_active=true;
        }
        else
        {
            is_active=false;
        }
        counter=0;
    }
    counter++;
}
unsigned int Effect::getState()
{
    return current_state;
}
void Effect::attachEntity(Entity *entity)
{
    if(entity!=0){
    m_entity_attached=entity;
    setPosition(entity->getPosition());
    sf::Vector2f scales(entity->getGlobalBounds().width/getGlobalBounds().width, entity->getGlobalBounds().height/getGlobalBounds().height);
    (scales.x <= scales.y) ? setScale(scales.x, scales.x) : setScale(scales.y, scales.y);
    }
}
void Effect::setPosition(sf::Vector2f pos){sf::Sprite::setPosition(pos);}
void Effect::setTexture(sf::Texture &Img)
{
    Entity::setTexture(Img);
    setTextureRect(sf::IntRect(0,0, getTexture()->getSize().x, Img.getSize().y/4));
}
bool Effect::getActive()
{
    return is_active;
}
void Effect::activate()
{
    is_active=true;
}
void Effect::draw(sf::RenderTarget* sys)
{
    if(is_active && sys!=0)
    {
        if(m_entity_attached!=0){setPosition(m_entity_attached->getPosition());}
        sys->draw(*this);
    }
}
